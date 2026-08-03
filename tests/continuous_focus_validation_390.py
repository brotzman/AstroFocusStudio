#!/usr/bin/env python3
"""Static integration contracts for continuous focus tracking in 3.9.0."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
BACKEND = (ROOT / "backend" / "backend.cpp").read_text(encoding="utf-8")
FRONTEND = (ROOT / "frontend" / "frontend.cpp").read_text(encoding="utf-8")
HELPER = (ROOT / "common" / "continuous_focus_logic.h").read_text(encoding="utf-8")
RUNNER = (ROOT / "scripts" / "Run-NativeTests.sh").read_text(encoding="utf-8")

checks: list[tuple[str, bool]] = []

def check(name: str, condition: bool) -> None:
    checks.append((name, condition))
    print(f"{name}: {'PASS' if condition else 'FAIL'}")

check("continuous focus exposes predictive, image and hybrid modes", all(token in BACKEND for token in ("CF_PREDICTIVE", "CF_IMAGE", "CF_HYBRID")))
check("continuous focus has explicit move and verification phases", all(token in BACKEND for token in ("CF_MOVING", "CF_SETTLING", "CF_VERIFYING")))
check("shared metric helper combines FWHM and HFR", "AfsCfMetric" in HELPER and "fwhm*0.72+hfr*0.56" in HELPER)
check("shared helper uses robust median aggregation", "AfsCfMedian" in HELPER and "sorted[16]" in HELPER)
check("shared helper bounds micro-correction size", "AfsCfStepFromDegradation" in HELPER and "AfsCfClampInt" in HELPER)

begin_move = re.search(r"static BOOL ContinuousFocusBeginMove\(.*?\n\}", BACKEND, re.DOTALL)
begin_body = begin_move.group(0) if begin_move else ""
check("motor movement is rejected while a main exposure is active", "if(g_exposing" in begin_body)
check("motor target is constrained to the configured safe zone", "g_safeMinPosition" in begin_body and "g_safeMaxPosition" in begin_body)
check("failed micro-correction pauses fail closed", "g_continuousFocusPaused=TRUE" in begin_body)

frame_match = re.search(r"static void ProcessCompletedFrame\(int purpose\)\{(?P<body>.*?)\n\}", BACKEND, re.DOTALL)
frame_body = frame_match.group("body") if frame_match else ""
check("tracking consumes only normal live frames", "purpose==1?ContinuousFocusOnLiveFrame():FALSE" in frame_body)
check("completed exposure is cleared before tracking can command the motor", frame_body.find("g_exposing=FALSE") >= 0 and frame_body.find("g_exposing=FALSE") < frame_body.find("ContinuousFocusOnLiveFrame"))
check("tracking can hold the next normal exposure during a correction", "continuousFocusHoldsNext" in frame_body)
check("no separate focus exposure series is started by frame processing", "StartExposure(2)" not in frame_body and "StartExposure(3)" not in frame_body)

on_frame = re.search(r"static BOOL ContinuousFocusOnLiveFrame\(\)\{(?P<body>.*?)\n\}", BACKEND, re.DOTALL)
on_body = on_frame.group("body") if on_frame else ""
check("low-star or low-confidence frames are discarded", "confidence<g_continuousFocusMinConfidence" in on_body and "g_usedCount<g_refocusMinStars" in on_body)
check("image decisions use a median frame window", "AfsCfMedian" in on_body and "g_continuousFocusMinFrames" in on_body)
check("predictive mode uses the learned temperature model", "g_tempSlope*g_focuserTemperature+g_tempIntercept" in on_body)
check("image mode requires sustained degradation before probing", "AfsCfDegradationPercent" in on_body and "degradation<trigger" in on_body)
check("verification requires measured improvement", "AfsCfImprovementPercent" in on_body and "g_continuousFocusMinImprovement" in on_body)
check("failed verification returns to the original position", "CF_MOVE_ROLLBACK" in on_body and "g_continuousFocusOrigin" in on_body)
check("failed image probe reverses the next exploratory direction", "rejectedMoveKind==CF_MOVE_IMAGE_PROBE" in on_body and "g_continuousFocusLastDirection=-g_continuousFocusLastDirection" in on_body)
check("repeated ambiguity can request a complete autofocus fallback", "ContinuousFocusRequestFallback" in on_body)
check("reference reset clears stale chart correction and target", "g_continuousFocusTarget=position" in BACKEND and "g_continuousFocusLastCorrection=0" in BACKEND)
check("accepted and rolled-back corrections publish the actual focus target", on_body.count("g_continuousFocusTarget=FocuserPosition()") >= 1 and "g_continuousFocusTarget=FocuserPosition()" in BACKEND)

check("legacy temperature compensation is suppressed in predictive tracking modes", "if(g_continuousFocusEnabled&&!g_continuousFocusPaused&&(g_continuousFocusMode==CF_PREDICTIVE||g_continuousFocusMode==CF_HYBRID))return;" in BACKEND)
check("legacy degradation autofocus does not race active continuous tracking", "if(g_continuousFocusEnabled&&!g_continuousFocusPaused)return FALSE;" in BACKEND)
check("manual focus movement rebuilds the tracking reference", "Manuelle Fokusbewegung · Nachführungsreferenz wird neu aufgebaut" in BACKEND)
check("filter offset changes rebuild the tracking reference", "Filteroffset angewendet · Nachführungsreferenz wird neu aufgebaut" in BACKEND)
check("successful full autofocus becomes the new tracking reference", "Bestätigter Autofokus wurde als neue Referenz" in BACKEND and "g_continuousFocusOrigin=g_afFinalPosition" in BACKEND and "g_continuousFocusTarget=g_afFinalPosition" in BACKEND)

for key in (
    "ContinuousFocusEnabled", "ContinuousFocusFallback", "ContinuousFocusMode",
    "ContinuousFocusMinFrames", "ContinuousFocusDeadband", "ContinuousFocusMaxStep",
    "ContinuousFocusConfidence", "ContinuousFocusImprovement", "ContinuousFocusSettleMs",
):
    check(f"setting is persisted: {key}", f'L"{key}"' in BACKEND)

for api_name in (
    "continuousFocus", "continuousFocusFallback", "continuousFocusMode",
    "continuousFocusMinFrames", "continuousFocusDeadband", "continuousFocusMaxStep",
    "continuousFocusConfidence", "continuousFocusImprovement", "continuousFocusSettleMs",
    "continuous-focus-reset", "continuous-focus-resume",
):
    check(f"local API exposes: {api_name}", f'"{api_name}"' in BACKEND)

for status_name in (
    "continuousFocusEnabled", "continuousFocusPhase", "continuousFocusState",
    "continuousFocusReason", "continuousFocusConfidence", "continuousFocusReferenceMetric",
    "continuousFocusEstimatedError", "continuousFocusDriftStepsPerMinute",
    "continuousFocusAccepted", "continuousFocusRejected",
):
    check(f"status exposes: {status_name}", f'\\\"{status_name}\\\"' in BACKEND)

check("frontend provides a dedicated tracking page", 'L"Nachführung"' in FRONTEND and "ID_TAB_CONTINUOUS" in FRONTEND)
check("frontend provides all three expert modes", all(label in FRONTEND for label in ('L"Prädiktiv"', 'L"Bildbasiert"', 'L"Hybrid"')))
check("frontend explicitly states no motion during a main exposure", "Während einer laufenden Hauptbelichtung wird der Fokussierer nie bewegt" in FRONTEND)
check("frontend honestly states guide/ONAG is not yet coupled", "Guide-/ONAG-Echtzeitquelle ist in 3.9.0 noch nicht gekoppelt" in FRONTEND)
check("frontend validates all numeric tracking limits before saving", all(token in FRONTEND for token in ("minFrames<3", "deadband<1", "maxStep<deadband", "confidence<30", "improvement<0.1", "settle<100")))
check("frontend provides reset and explicit resume controls", "ID_CF_RESET" in FRONTEND and "ID_CF_RESUME" in FRONTEND)
check("frontend draws focus position, target and correction markers", "DrawContinuousFocusPage" in FRONTEND and "g_cfUi[i].correction" in FRONTEND)
check("native sanitizer suite includes the continuous focus helper", "continuous_focus_logic_validation_390.cpp" in RUNNER)

failed = [name for name, ok in checks if not ok]
print(f"SUMMARY {len(checks) - len(failed)}/{len(checks)}")
if failed:
    raise SystemExit(1)
