# Traceability Report

## Summary Metrics

- Total System Requirements (SYS-REQ): 49
- Total Software Requirements (SWE-REQ): 38
- Total Software Units: 6
- Total Code Files: 14
- Total Unit Tests: 24
- Total System Tests: 7
- Coverage:
  - SW-REQs with Unit Tests: 33/38 (86.8%)
  - SYS-REQs with ST Cases: 41/49 (83.7%)
  - SW-REQs with Code: 33/38 (86.8%)
  - SW Units with UT: 6/6 (100%)

## Forward Trace Matrix
| SYS | SWE | Unit | Code File | UT | ST |
|-----|-----|------|-----------|----|----|
| SYS-REQ-001 | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED |
| SYS-REQ-002 | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED |
| SYS-REQ-003 | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED |
| SYS-REQ-004 | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED |
| SYS-REQ-005 | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED |
| SYS-REQ-006 | SWE-REQ-001 | Command Handler | code/inc/command_handler.h | CMDHND-TC-01 | SYS-TC-002 |
| SYS-REQ-007 | SWE-REQ-003 | Flap Control Unit | code/inc/flap_control.h | FLAP-TC-01 | SYS-TC-002 |
| SYS-REQ-008 | SWE-REQ-004 | Flap Control Unit | code/inc/flap_control.h | FLAP-TC-02 | SYS-TC-002 |
| SYS-REQ-009 | SWE-REQ-009 | Feedback (ADC Acquisition & Mapping) Unit | code/inc/feedback_adc.h | FEED-TC-02 | SYS-TC-002, SYS-TC-004 |
| SYS-REQ-010 | SWE-REQ-005 | Motor Control Unit | code/inc/motor_control.h | MOTOR-TC-01 | SYS-TC-005 |
| SYS-REQ-011 | SWE-REQ-005 | Motor Control Unit | code/inc/motor_control.h | MOTOR-TC-01 | SYS-TC-002, SYS-TC-005 |
| SYS-REQ-012 | SWE-REQ-006 | Motor Control Unit | code/inc/motor_control.h | MOTOR-TC-02 | SYS-TC-002, SYS-TC-005, SYS-TC-007 |
| SYS-REQ-013 | SWE-REQ-007 | Motor Control Unit | code/inc/motor_control.h | MOTOR-TC-03 | SYS-TC-001 |
| SYS-REQ-014 | SWE-REQ-008 | Feedback (ADC Acquisition & Mapping) Unit | code/inc/feedback_adc.h | FEED-TC-01 | SYS-TC-004 |
| SYS-REQ-015 | SWE-REQ-008 | Feedback (ADC Acquisition & Mapping) Unit | code/inc/feedback_adc.h | FEED-TC-01 | SYS-TC-002, SYS-TC-004 |
| SYS-REQ-016 | SWE-REQ-009 | Feedback (ADC Acquisition & Mapping) Unit | code/inc/feedback_adc.h | FEED-TC-02 | SYS-TC-002, SYS-TC-004 |
| SYS-REQ-017 | SWE-REQ-010 | Feedback (ADC Acquisition & Mapping) Unit | code/inc/feedback_adc.h | FEED-TC-03 | SYS-TC-003, SYS-TC-005 |
| SYS-REQ-018 | SWE-REQ-001 | Command Handler | code/inc/command_handler.h | CMDHND-TC-01 | NOT TRACED |
| SYS-REQ-019 | SWE-REQ-001 | Command Handler | code/inc/command_handler.h | CMDHND-TC-01 | SYS-TC-002 |
| SYS-REQ-020 | SWE-REQ-002 | Command Handler | code/inc/command_handler.h | CMDHND-TC-02 | SYS-TC-003 |
| SYS-REQ-021 | SWE-REQ-002 | Command Handler | code/inc/command_handler.h | CMDHND-TC-02 | SYS-TC-003 |
| SYS-REQ-022 | SWE-REQ-011 | Indication (LED Management) Unit | code/inc/indication_led.h | IND-TC-01 | SYS-TC-001, SYS-TC-006 |
| SYS-REQ-023 | SWE-REQ-012 | Indication (LED Management) Unit | code/inc/indication_led.h | IND-TC-02 | SYS-TC-001, SYS-TC-002, SYS-TC-004, SYS-TC-006, SYS-TC-007 |
| SYS-REQ-024 | SWE-REQ-013 | Indication (LED Management) Unit | code/inc/indication_led.h | IND-TC-03 | SYS-TC-006 |
| SYS-REQ-025 | SWE-REQ-020 | Flap Control Unit | code/inc/flap_control.h | FLAP-TC-04 | SYS-TC-001 |
| SYS-REQ-026 | SWE-REQ-021 | Feedback (ADC Acquisition & Mapping) Unit | code/inc/feedback_adc.h | FEED-TC-04 | SYS-TC-001, SYS-TC-004, SYS-TC-006 |
| SYS-REQ-027 | SWE-REQ-022 | Flap Control Unit | code/inc/flap_control.h | FLAP-TC-04 | NOT TRACED |
| SYS-REQ-028 | SWE-REQ-023 | Flap Control Unit | code/inc/flap_control.h | FLAP-TC-01 | SYS-TC-002 |
| SYS-REQ-029 | SWE-REQ-024 | Flap Control Unit | code/inc/flap_control.h | FLAP-TC-04 | SYS-TC-003 |
| SYS-REQ-030 | SWE-REQ-015 | Command Handler | code/inc/command_handler.h | CMDHND-TC-01 | NOT TRACED |
| SYS-REQ-031 | SWE-REQ-016 | Feedback (ADC Acquisition & Mapping) Unit | code/inc/feedback_adc.h | FEED-TC-04 | NOT TRACED |
| SYS-REQ-032 | SWE-REQ-017 | Motor Control Unit | code/inc/motor_control.h | MOTOR-TC-01 | NOT TRACED |
| SYS-REQ-033 | SWE-REQ-017 | Motor Control Unit | code/inc/motor_control.h | MOTOR-TC-01 | NOT TRACED |
| SYS-REQ-034 | SWE-REQ-018 | Indication (LED Management) Unit | code/inc/indication_led.h | IND-TC-01 | NOT TRACED |
| SYS-REQ-035 | SWE-REQ-019 | Static Configuration Unit | code/inc/static_config.h | SCFG-TC-01 | NOT TRACED |
| SYS-REQ-036 | SWE-REQ-032 | Motor Control Unit | code/inc/motor_control.h | MOTOR-TC-04 | NOT TRACED |
| SYS-REQ-037 | SWE-REQ-037 | Indication (LED Management) Unit | code/inc/indication_led.h | IND-TC-02 | NOT TRACED |
| SYS-REQ-038 | SWE-REQ-026 | Static Configuration Unit | code/inc/static_config.h | SCFG-TC-01 | NOT TRACED |
| SYS-REQ-039 | SWE-REQ-032 | Motor Control Unit | code/inc/motor_control.h | MOTOR-TC-04 | NOT TRACED |
| SYS-REQ-040 | SWE-REQ-033 | Command Handler | code/inc/command_handler.h | CMDHND-TC-01 | NOT TRACED |
| SYS-REQ-041 | SWE-REQ-033 | Command Handler | code/inc/command_handler.h | CMDHND-TC-01 | SYS-TC-002, SYS-TC-005 |
| SYS-REQ-042 | SWE-REQ-029 | Flap Control Unit | code/inc/flap_control.h | FLAP-TC-03 | SYS-TC-003, SYS-TC-005 |
| SYS-REQ-043 | SWE-REQ-030 | Command Handler | code/inc/command_handler.h | CMDHND-TC-02 | SYS-TC-003 |
| SYS-REQ-044 | SWE-REQ-035 | Static Configuration Unit | code/inc/static_config.h | SCFG-TC-01 | NOT TRACED |
| SYS-REQ-045 | SWE-REQ-036 | Static Configuration Unit | code/inc/static_config.h | SCFG-TC-01 | NOT TRACED |
| SYS-REQ-046 | SWE-REQ-014 | NOT TRACED | NOT TRACED | NOT TRACED | NOT TRACED |
| SYS-REQ-047 | SWE-REQ-027 | Static Configuration Unit | code/inc/static_config.h | SCFG-TC-01 | NOT TRACED |
| SYS-REQ-048 | SWE-REQ-037 | Indication (LED Management) Unit | code/inc/indication_led.h | IND-TC-03 | SYS-TC-007 |
| SYS-REQ-049 | SWE-REQ-038 | Indication (LED Management) Unit | code/inc/indication_led.h | IND-TC-02 | SYS-TC-002, SYS-TC-004, SYS-TC-007 |

## Backward Trace Matrix
| ST | UT | Code | Unit | SWE | SYS |
|----|----|------|------|-----|-----|
| SYS-TC-001 | FLAP-TC-04 | code/inc/flap_control.h | Flap Control Unit | SWE-REQ-020 | SYS-REQ-025 |
| SYS-TC-001 | IND-TC-01 | code/inc/indication_led.h | Indication (LED Management) Unit | SWE-REQ-011 | SYS-REQ-022 |
| SYS-TC-001 | IND-TC-02 | code/inc/indication_led.h | Indication (LED Management) Unit | SWE-REQ-012 | SYS-REQ-023 |
| SYS-TC-001 | MOTOR-TC-03 | code/inc/motor_control.h | Motor Control Unit | SWE-REQ-007 | SYS-REQ-013 |
| SYS-TC-001 | FEED-TC-04 | code/inc/feedback_adc.h | Feedback (ADC Acquisition & Mapping) Unit | SWE-REQ-021 | SYS-REQ-026 |
| SYS-TC-002 | CMDHND-TC-01 | code/inc/command_handler.h | Command Handler | SWE-REQ-001 | SYS-REQ-006 |
| SYS-TC-002 | FLAP-TC-01 | code/inc/flap_control.h | Flap Control Unit | SWE-REQ-003 | SYS-REQ-007 |
| SYS-TC-002 | FLAP-TC-02 | code/inc/flap_control.h | Flap Control Unit | SWE-REQ-004 | SYS-REQ-008 |
| SYS-TC-002 | FEED-TC-02 | code/inc/feedback_adc.h | Feedback (ADC Acquisition & Mapping) Unit | SWE-REQ-009 | SYS-REQ-009 |
| SYS-TC-002 | MOTOR-TC-01 | code/inc/motor_control.h | Motor Control Unit | SWE-REQ-005 | SYS-REQ-011 |
| SYS-TC-002 | MOTOR-TC-02 | code/inc/motor_control.h | Motor Control Unit | SWE-REQ-006 | SYS-REQ-012 |
| SYS-TC-002 | IND-TC-02 | code/inc/indication_led.h | Indication (LED Management) Unit | SWE-REQ-012 | SYS-REQ-023 |
| SYS-TC-002 | CMDHND-TC-01 | code/inc/command_handler.h | Command Handler | SWE-REQ-001 | SYS-REQ-019 |
| SYS-TC-003 | CMDHND-TC-02 | code/inc/command_handler.h | Command Handler | SWE-REQ-002 | SYS-REQ-020 |
| SYS-TC-003 | FLAP-TC-03 | code/inc/flap_control.h | Flap Control Unit | SWE-REQ-024 | SYS-REQ-029 |
| SYS-TC-004 | FEED-TC-01 | code/inc/feedback_adc.h | Feedback (ADC Acquisition & Mapping) Unit | SWE-REQ-008 | SYS-REQ-014 |
| SYS-TC-004 | FEED-TC-02 | code/inc/feedback_adc.h | Feedback (ADC Acquisition & Mapping) Unit | SWE-REQ-009 | SYS-REQ-015 |
| SYS-TC-005 | MOTOR-TC-01 | code/inc/motor_control.h | Motor Control Unit | SWE-REQ-005 | SYS-REQ-010 |
| SYS-TC-005 | FLAP-TC-03 | code/inc/flap_control.h | Flap Control Unit | SWE-REQ-029 | SYS-REQ-042 |
| SYS-TC-006 | IND-TC-03 | code/inc/indication_led.h | Indication (LED Management) Unit | SWE-REQ-013 | SYS-REQ-024 |
| SYS-TC-007 | IND-TC-03 | code/inc/indication_led.h | Indication (LED Management) Unit | SWE-REQ-038 | SYS-REQ-048 |
| SYS-TC-007 | FLAP-TC-01 | code/inc/flap_control.h | Flap Control Unit | SWE-REQ-003 | SYS-REQ-012 |

## Coverage Gaps

- SYS Requirements without Trace to ST: SYS-REQ-001, SYS-REQ-002, SYS-REQ-003, SYS-REQ-004, SYS-REQ-005, SYS-REQ-018, SYS-REQ-027, SYS-REQ-030, SYS-REQ-031, SYS-REQ-032, SYS-REQ-033, SYS-REQ-034, SYS-REQ-035, SYS-REQ-036, SYS-REQ-037, SYS-REQ-038, SYS-REQ-039, SYS-REQ-040, SYS-REQ-044, SYS-REQ-045, SYS-REQ-046, SYS-REQ-047
- SWE Requirements without UT: SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-019, SWE-REQ-025
- SWE Requirements without Code: SWE-REQ-014, SWE-REQ-018, SWE-REQ-019, SWE-REQ-025
- Orphan Unit Test Cases: Not detected
- Orphan Code Files: Not detected

