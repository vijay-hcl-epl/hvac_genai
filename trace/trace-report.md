# Traceability Report: HVAC Flap Actuator

## Summary Metrics

- Branch: `demojun-10a`
- Commit used by trace input bundle: `fe23d620c0925641f6c244c1a7859889cabd98e7`
- Total System Requirements (SYS): **33**
- Total Software Requirements (SWE): **32**
- Total Software Units: **7**
- Total Code Files: **13** (6 headers + 7 source files)
- Total Unit Test Cases (UT): **22**
- Total System Test Cases (ST): **13**

### Coverage

Coverage below is based on the traceability information explicitly present in the repository artifacts. It does **not** mean the tests were executed.

- SYS-REQs → SWE-REQs: **32/33 = 97%**
- SWE-REQs → Software Units: **26/32 = 81%**
- SWE Units → Code files: **6/7 = 86%** (the `main.c` application entry point has no explicit SWE-REQ trace)
- SWE-REQs allocated to UT: **26/32 = 81%**
- SYS-REQs with explicit named ST mapping: **21/33 = 64%**
- ST document additionally uses `SYS-TC-013` as a catch-all statement for functional `SYS-REQ-001–033`; this is not a requirement-by-requirement mapping.

### Important observation

The branch contains traceability artifacts, but the current trace is **not as complete as the older `hvdemo-feb18_1` report**. In particular, SWE-REQ-021, 022, 029, 030, 031 and 032 are not explicitly allocated to a software unit in the SWE.3 traceability sections, and several system requirements are only covered by the broad end-to-end test `SYS-TC-013`.

## Forward Trace Matrix

| SYS | SWE | Unit | Code File(s) | UT Case(s) | ST Case(s) |
|---|---|---|---|---|---|
| SYS-REQ-001 | SWE-REQ-001 | Command Manager | `code/inc/command_manager.h`, `code/src/command_manager.c` | `TC_CM_001, TC_CM_002` | `SYS-TC-002` |
| SYS-REQ-002 | SWE-REQ-004, SWE-REQ-023 | Flap Control Coordinator | `code/inc/flap_control_coordinator.h`, `code/src/flap_control_coordinator.c` | `TC_FC_001, TC_FC_002` | `SYS-TC-002` |
| SYS-REQ-003 | SWE-REQ-005, SWE-REQ-023 | Flap Control Coordinator | `code/inc/flap_control_coordinator.h`, `code/src/flap_control_coordinator.c` | `TC_FC_002, TC_FC_005` | `SYS-TC-002` |
| SYS-REQ-004 | SWE-REQ-002 | Command Manager | `code/inc/command_manager.h`, `code/src/command_manager.c` | `TC_CM_003, TC_CM_004` | `SYS-TC-003` |
| SYS-REQ-005 | SWE-REQ-010, SWE-REQ-025 | Feedback Processing | `code/inc/feedback_processing.h`, `code/src/feedback_processing.c` | `TC_FB_001` | `SYS-TC-007` |
| SYS-REQ-006 | SWE-REQ-006 | Motor Control | `code/inc/motor_control.h`, `code/src/motor_control.c` | `TC_MC_001, TC_MC_002` | `SYS-TC-002, SYS-TC-009` |
| SYS-REQ-007 | SWE-REQ-007 | Motor Control | `code/inc/motor_control.h`, `code/src/motor_control.c` | `TC_MC_003` | `SYS-TC-002, SYS-TC-004, SYS-TC-009, SYS-TC-010` |
| SYS-REQ-008 | SWE-REQ-008 | Motor Control | `code/inc/motor_control.h`, `code/src/motor_control.c` | `TC_MC_001, TC_MC_002, TC_MC_004` | `SYS-TC-002, SYS-TC-009` |
| SYS-REQ-009 | SWE-REQ-009, SWE-REQ-018 | Feedback Processing / Hardware Abstraction | `code/inc/feedback_processing.h`, `code/src/feedback_processing.c`, `code/inc/hardware_abstraction.h`, `code/src/hardware_abstraction.c` | `TC_FB_001` | `SYS-TC-007` |
| SYS-REQ-010 | SWE-REQ-010 | Feedback Processing | `code/inc/feedback_processing.h`, `code/src/feedback_processing.c` | `TC_FB_001` | `SYS-TC-007` |
| SYS-REQ-011 | SWE-REQ-011, SWE-REQ-027 | Feedback Processing / Flap Control Coordinator | `code/inc/feedback_processing.h`, `code/src/feedback_processing.c`, `code/inc/flap_control_coordinator.h`, `code/src/flap_control_coordinator.c` | `TC_FB_002` | `SYS-TC-004, SYS-TC-008` |
| SYS-REQ-012 | SWE-REQ-001, SWE-REQ-016, SWE-REQ-022 | Command Manager / Main | `code/inc/command_manager.h`, `code/src/command_manager.c`, `code/src/main.c` | `TC_CM_001, TC_CM_002` | —* |
| SYS-REQ-013 | SWE-REQ-001, SWE-REQ-002 | Command Manager | `code/inc/command_manager.h`, `code/src/command_manager.c` | `TC_CM_001, TC_CM_002, TC_CM_003, TC_CM_004` | `SYS-TC-003` |
| SYS-REQ-014 | SWE-REQ-028 | Command Manager | `code/inc/command_manager.h`, `code/src/command_manager.c` | `TC_CM_003, TC_CM_004` | `SYS-TC-003` |
| SYS-REQ-015 | SWE-REQ-013, SWE-REQ-015 | LED Management | `code/inc/led_management.h`, `code/src/led_management.c` | `TC_LED_001, TC_LED_003` | `SYS-TC-001, SYS-TC-011` |
| SYS-REQ-016 | SWE-REQ-014, SWE-REQ-015 | LED Management | `code/inc/led_management.h`, `code/src/led_management.c` | `TC_LED_002, TC_LED_003` | `SYS-TC-001, SYS-TC-012` |
| SYS-REQ-017 | SWE-REQ-020, SWE-REQ-021 | Hardware Abstraction / LED Management / Main | `code/inc/hardware_abstraction.h`, `code/src/hardware_abstraction.c`, `code/inc/led_management.h`, `code/src/led_management.c`, `code/src/main.c` | `TC_HA_001, TC_LED_001` | `SYS-TC-001, SYS-TC-011` |
| SYS-REQ-018 | SWE-REQ-022 | Main / Command Manager / Feedback Processing | `code/src/main.c`, `code/src/command_manager.c`, `code/src/feedback_processing.c` | — | `SYS-TC-013*` |
| SYS-REQ-019 | SWE-REQ-004, SWE-REQ-005, SWE-REQ-015, SWE-REQ-023 | Flap Control Coordinator / LED Management | corresponding coordinator and LED files | `TC_FC_001, TC_FC_002, TC_FC_004, TC_LED_002, TC_LED_003` | `SYS-TC-005, SYS-TC-008, SYS-TC-012` |
| SYS-REQ-020 | SWE-REQ-024, SWE-REQ-028 | Command Manager / Flap Control Coordinator | corresponding command and coordinator files | `TC_CM_003, TC_CM_004, TC_FC_003` | `SYS-TC-013*` |
| SYS-REQ-021 | SWE-REQ-016 | Command Manager | `code/inc/command_manager.h`, `code/src/command_manager.c` | `TC_CM_001, TC_CM_002` | `SYS-TC-013*` |
| SYS-REQ-022 | SWE-REQ-017 | Hardware Abstraction / Motor Control | `code/inc/hardware_abstraction.h`, `code/src/hardware_abstraction.c`, `code/inc/motor_control.h`, `code/src/motor_control.c` | `TC_HA_002, TC_MC_001, TC_MC_002` | `SYS-TC-013*` |
| SYS-REQ-023 | SWE-REQ-018 | Hardware Abstraction / Feedback Processing | `code/inc/hardware_abstraction.h`, `code/src/hardware_abstraction.c`, `code/inc/feedback_processing.h`, `code/src/feedback_processing.c` | `TC_HA_003, TC_FB_001` | `SYS-TC-013*` |
| SYS-REQ-024 | SWE-REQ-019 | Hardware Abstraction / LED Management | `code/inc/hardware_abstraction.h`, `code/src/hardware_abstraction.c`, `code/inc/led_management.h`, `code/src/led_management.c` | `TC_HA_002, TC_HA_003` | `SYS-TC-013*` |
| SYS-REQ-025 | — | — (system constraint) | — | — | `SYS-TC-010` |
| SYS-REQ-026 | SWE-REQ-025 | Feedback Processing | `code/inc/feedback_processing.h`, `code/src/feedback_processing.c` | — | `SYS-TC-013*` |
| SYS-REQ-027 | SWE-REQ-027 | Flap Control Coordinator / Motor Control | `code/inc/flap_control_coordinator.h`, `code/src/flap_control_coordinator.c`, `code/inc/motor_control.h`, `code/src/motor_control.c` | `TC_MC_003` | `SYS-TC-004, SYS-TC-010` |
| SYS-REQ-028 | SWE-REQ-030 | — (performance requirement) | — | — | `SYS-TC-013*` |
| SYS-REQ-029 | SWE-REQ-027 | Flap Control Coordinator / Motor Control | corresponding files | `TC_MC_003` | `SYS-TC-003, SYS-TC-004, SYS-TC-006` |
| SYS-REQ-030 | SWE-REQ-029 | — (robustness requirement) | — | — | `SYS-TC-006` |
| SYS-REQ-031 | SWE-REQ-031 | — (resource constraint) | — | — | `SYS-TC-013*` |
| SYS-REQ-032 | SWE-REQ-026 | Flap Control Coordinator / LED Management | corresponding files | `TC_FC_004, TC_LED_002` | `SYS-TC-013*` |
| SYS-REQ-033 | SWE-REQ-032 | — (testability requirement) | — | — | `SYS-TC-013*` |

\* `SYS-TC-013` states that it covers all functional `SYS-REQ-001–033`, but it is a broad catch-all rather than an individual requirement mapping.

## Reverse Trace Observations

- All six primary functional software components have explicit SWE.1/SWE.3 traceability.
- SWE-REQ-021, SWE-REQ-022, SWE-REQ-029, SWE-REQ-030, SWE-REQ-031 and SWE-REQ-032 do not have explicit software-unit trace entries in the current SWE.3 traceability sections.
- Unit testing is limited to the six named units; the UT plan explicitly uses mocked peripherals and does not require real hardware.
- The ST plan defines 13 system test cases on a real hardware bench.
- The ST plan provides explicit requirement IDs for 21 SYS requirements; the remaining coverage is mainly asserted through the broad end-to-end `SYS-TC-013`.
- The repository's generated code includes simulation/TODO placeholders in the hardware abstraction layer and a stub main loop, so this traceability report should not be interpreted as evidence of completed production implementation or executed qualification tests.

## Conclusion

The `demojun-10a` branch has a usable end-to-end traceability structure:

**System Requirements → Software Requirements → Software Units → Code → Unit Tests → System Tests**

However, compared with the older traceability report format, the current branch has **measurable trace gaps**, especially for non-functional requirements and explicit system-test mapping. The trace structure is present, but the report should be considered a **design-time traceability/coverage report**, not a test-execution or compliance report.
