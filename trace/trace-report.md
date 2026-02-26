# HVAC Flap Actuator Traceability Report

## Summary Metrics

| Metric                | Count |
|-----------------------|-------|
| System Requirements   | 48    |
| Software Requirements | 39    |
| Software Units        | 7     |
| Code Files            | 14    |
| Unit Test Cases       | 41    |
| System Test Cases     | 12    |

Coverage Metrics:
- SWE Coverage (SYS → SWE): 100% (all SYS-REQ mapped in SWE-REQs)
- SW Unit to Requirement: 100% (all SWE-REQs allocate to SW units)
- Unit Test Coverage: 100% (all SW units have UT cases)
- System Test Coverage: 100% (all major operational scenarios)

## Forward Trace Matrix

| SYS | SWE | Unit | Code File | UT | ST |
|-----|-----|------|-----------|----|----|
| SYS-REQ-001 | SWE-REQ-001 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-01 | SYS-TC-003 |
| SYS-REQ-002 | SWE-REQ-001 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-01 | SYS-TC-003 |
| SYS-REQ-003 | SWE-REQ-005 | State Machine/Control Logic | code/inc/state_machine.h | TC-SM-02 | SYS-TC-004 |
| SYS-REQ-004 | SWE-REQ-002 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-02 | SYS-TC-005 |
| SYS-REQ-005 | SWE-REQ-011 | ADC Feedback Unit | code/inc/adc_feedback.h | TC-ADC-03 | SYS-TC-008 |
| SYS-REQ-006 | SWE-REQ-003 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-06 | SYS-TC-007 |
| SYS-REQ-007 | SWE-REQ-007 | Motor Control Unit | code/inc/motor_control.h | TC-MOT-01 | SYS-TC-010 |
| SYS-REQ-008 | SWE-REQ-004 | State Machine/Control Logic | code/inc/state_machine.h | TC-SM-01 | SYS-TC-004 |
| SYS-REQ-009 | SWE-REQ-007 | Motor Control Unit | code/inc/motor_control.h | TC-MOT-01 | SYS-TC-004 |
| SYS-REQ-010 | SWE-REQ-009 | Motor Control Unit | code/inc/motor_control.h | TC-MOT-04 | SYS-TC-010 |
| SYS-REQ-011 | SWE-REQ-008 | Motor Control Unit | code/inc/motor_control.h | TC-MOT-06 | SYS-TC-010 |
| SYS-REQ-012 | SWE-REQ-010 | ADC Feedback Unit | code/inc/adc_feedback.h | TC-ADC-01 | SYS-TC-004 |
| SYS-REQ-013 | SWE-REQ-010 | ADC Feedback Unit | code/inc/adc_feedback.h | TC-ADC-01 | SYS-TC-009 |
| SYS-REQ-014 | SWE-REQ-014 | Status Indication Unit | code/inc/status_indication.h | TC-STAT-01 | SYS-TC-011 |
| SYS-REQ-015 | SWE-REQ-011 | ADC Feedback Unit | code/inc/adc_feedback.h | TC-ADC-03 | SYS-TC-008 |
| SYS-REQ-016 | SWE-REQ-012 | ADC Feedback Unit | code/inc/adc_feedback.h | TC-ADC-02 | SYS-TC-006 |
| SYS-REQ-017 | SWE-REQ-001 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-04 | SYS-TC-005 |
| SYS-REQ-018 | SWE-REQ-001 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-04 | SYS-TC-003 |
| SYS-REQ-019 | SWE-REQ-030 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-03 | SYS-TC-005 |
| SYS-REQ-020 | SWE-REQ-014 | Status Indication Unit | code/inc/status_indication.h | TC-STAT-01 | SYS-TC-003 |
| SYS-REQ-021 | SWE-REQ-015 | Status Indication Unit | code/inc/status_indication.h | TC-STAT-04 | SYS-TC-011 |
| SYS-REQ-022 | SWE-REQ-016 | Status Indication Unit | code/inc/status_indication.h | TC-STAT-03 | SYS-TC-011 |
| SYS-REQ-023 | SWE-REQ-022 | State Machine/Control Logic | code/inc/state_machine.h | TC-SM-02 | SYS-TC-001 |
| SYS-REQ-024 | SWE-REQ-023 | State Machine/Control Logic | code/inc/state_machine.h | TC-SM-02 | SYS-TC-001 |
| SYS-REQ-025 | SWE-REQ-024 | State Machine/Control Logic | code/inc/state_machine.h | TC-SM-02 | SYS-TC-002 |
| SYS-REQ-026 | SWE-REQ-025 | State Machine/Control Logic | code/inc/state_machine.h | TC-SM-03 | SYS-TC-002 |
| SYS-REQ-027 | SWE-REQ-006 | State Machine/Control Logic | code/inc/state_machine.h | TC-SM-01 | SYS-TC-002 |
| SYS-REQ-028 | SWE-REQ-017 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-01 | SYS-TC-003 |
| SYS-REQ-029 | SWE-REQ-017 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-04 | SYS-TC-003 |
| SYS-REQ-030 | SWE-REQ-019 | ADC Feedback Unit | code/inc/adc_feedback.h | TC-ADC-04 | SYS-TC-008 |
| SYS-REQ-031 | SWE-REQ-020 | Status Indication Unit | code/inc/status_indication.h | TC-STAT-04 | SYS-TC-011 |
| SYS-REQ-032 | SWE-REQ-027 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-06 | SYS-TC-005 |
| SYS-REQ-033 | SWE-REQ-035 | Configuration Manager | code/inc/config_manager.h | TC-CONF-01 | SYS-TC-001 |
| SYS-REQ-034 | SWE-REQ-035 | Configuration Manager | code/inc/config_manager.h | TC-CONF-01 | SYS-TC-001 |
| SYS-REQ-035 | SWE-REQ-035 | Configuration Manager | code/inc/config_manager.h | TC-CONF-01 | SYS-TC-001 |
| SYS-REQ-036 | SWE-REQ-021 | Configuration Manager | code/inc/config_manager.h | TC-CONF-04 | SYS-TC-002 |
| SYS-REQ-037 | SWE-REQ-031 | Error Handling Unit | code/inc/error_handler.h | TC-ERR-05 | SYS-TC-002 |
| SYS-REQ-038 | SWE-REQ-032 | State Machine/Control Logic | code/inc/state_machine.h | TC-SM-04 | SYS-TC-009 |
| SYS-REQ-039 | SWE-REQ-008 | Motor Control Unit | code/inc/motor_control.h | TC-MOT-03 | SYS-TC-009 |
| SYS-REQ-040 | SWE-REQ-034 | State Machine/Control Logic | code/inc/state_machine.h | TC-SM-04 | SYS-TC-007 |
| SYS-REQ-041 | SWE-REQ-029 | Error Handling Unit | code/inc/error_handler.h | TC-ERR-01 | SYS-TC-006 |
| SYS-REQ-042 | SWE-REQ-029 | Error Handling Unit | code/inc/error_handler.h | TC-ERR-03 | SYS-TC-006 |
| SYS-REQ-043 | SWE-REQ-030 | Error Handling Unit | code/inc/error_handler.h | TC-ERR-05 | SYS-TC-007 |
| SYS-REQ-044 | SWE-REQ-035 | Configuration Manager | code/inc/config_manager.h | TC-CONF-01 | SYS-TC-009 |
| SYS-REQ-045 | SWE-REQ-036 | Motor Control Unit | code/inc/motor_control.h | TC-MOT-06 | SYS-TC-009 |
| SYS-REQ-046 | SWE-REQ-003 | Command Interface Unit | code/inc/command_interface.h | TC-CMDI-06 | SYS-TC-007 |
| SYS-REQ-047 | SWE-REQ-037 | Status Indication Unit | code/inc/status_indication.h | TC-STAT-03 | SYS-TC-009 |
| SYS-REQ-048 | SWE-REQ-038 | Status Indication Unit | code/inc/status_indication.h | TC-STAT-03 | SYS-TC-009 |

## Backward Trace Matrix

| ST | UT | Code | Unit | SWE | SYS |
|----|----|------|------|-----|-----|
| SYS-TC-001 | TC-SM-02 | code/inc/state_machine.h | State Machine/Control Logic | SWE-REQ-023 | SYS-REQ-024 |
| SYS-TC-002 | TC-SM-03 | code/inc/state_machine.h | State Machine/Control Logic | SWE-REQ-025 | SYS-REQ-026 |
| SYS-TC-003 | TC-CMDI-01 | code/inc/command_interface.h | Command Interface Unit | SWE-REQ-001 | SYS-REQ-002 |
| SYS-TC-004 | TC-SM-01 | code/inc/state_machine.h | State Machine/Control Logic | SWE-REQ-004 | SYS-REQ-008 |
| SYS-TC-005 | TC-CMDI-02 | code/inc/command_interface.h | Command Interface Unit | SWE-REQ-002 | SYS-REQ-004 |
| SYS-TC-006 | TC-ADC-02 | code/inc/adc_feedback.h | ADC Feedback Unit | SWE-REQ-012 | SYS-REQ-016 |
| SYS-TC-007 | TC-SM-04 | code/inc/state_machine.h | State Machine/Control Logic | SWE-REQ-034 | SYS-REQ-040 |
| SYS-TC-008 | TC-ADC-03 | code/inc/adc_feedback.h | ADC Feedback Unit | SWE-REQ-011 | SYS-REQ-015 |
| SYS-TC-009 | TC-STAT-03 | code/inc/status_indication.h | Status Indication Unit | SWE-REQ-016 | SYS-REQ-022 |
| SYS-TC-010 | TC-MOT-04 | code/inc/motor_control.h | Motor Control Unit | SWE-REQ-009 | SYS-REQ-010 |
| SYS-TC-011 | TC-STAT-04 | code/inc/status_indication.h | Status Indication Unit | SWE-REQ-015 | SYS-REQ-021 |
| SYS-TC-012 | TC-SM-01 | code/inc/state_machine.h | State Machine/Control Logic | SWE-REQ-024 | SYS-REQ-025 |

## Coverage Gaps

- SYS Requirements without ST: None
- SWE Requirements without UT: None
- SWE Requirements without Code: None
- Orphan Test Cases: None
- Orphan Code Files: None

