## Traceability Report: HVAC Air Flap Actuator (inf-demo)

### A) Summary Metrics

| Artifact Type   | Count |
|-----------------|-------|
| System Requirements (SYS-REQ)           | 37    |
| Software Requirements (SWE-REQ)         | 38    |
| SW Units                                | 7     |
| Code Files                              | 16    |
| Unit Test Cases (UT: unique)            | 8     |
| System Test Cases (ST: unique)          | 12    |

> **Coverage Calculation:**
- SWE-REQ→SYS-REQ mapping: 36/37 (97%)
- UT covers SWE-REQs: 13 unique SWE-REQs covered by direct test cases.
- ST covers SYS-REQs: 22 unique SYS-REQs tested out of 37 total.
- Code files mapped to specific SW Units: 13/16 directly referenced in bundle.

### B) Forward Trace Matrix
| SYS           | SWE                        | Unit                          | Code File                             | UT           | ST          |
|---------------|----------------------------|-------------------------------|---------------------------------------|--------------|-------------|
| SYS-REQ-001   | SWE-REQ-001, SWE-REQ-005   | Command Interface             | code/inc/command_interface.h,<br>code/src/command_interface.c | CI_TC_01   | SYS-TC-003, SYS-TC-012 |
| SYS-REQ-002   | SWE-REQ-002, SWE-REQ-005   | Command Interface             | code/inc/command_interface.h,<br>code/src/command_interface.c | CI_TC_02   | SYS-TC-003, SYS-TC-012 |
| SYS-REQ-003   | SWE-REQ-003, SWE-REQ-006   | Command Interface             | code/inc/command_interface.h,<br>code/src/command_interface.c | CI_TC_03   | SYS-TC-004, SYS-TC-012 |
| SYS-REQ-004   | SWE-REQ-003                | Command Interface             | code/inc/command_interface.h          | CI_TC_03     | NOT TRACED  |
| SYS-REQ-005   | SWE-REQ-008                | Flap Movement/Motor Control   | code/inc/flap_motor_control.h,<br>code/src/flap_motor_control.c | NOT TRACED   | SYS-TC-004, SYS-TC-010 |
| SYS-REQ-006   | SWE-REQ-009                | Flap Movement/Motor Control   | code/inc/flap_motor_control.h,<br>code/src/flap_motor_control.c | NOT TRACED   | SYS-TC-010 |
| SYS-REQ-007   | SWE-REQ-007                | Flap Movement/Motor Control   | code/inc/flap_motor_control.h         | NOT TRACED   | NOT TRACED  |
| SYS-REQ-008   | SWE-REQ-010                | Position Feedback Processing  | code/inc/position_feedback.h,<br>code/src/position_feedback.c | PF_TC_01   | SYS-TC-002 |
| SYS-REQ-009   | SWE-REQ-011                | Position Feedback Processing  | code/inc/position_feedback.h          | PF_TC_02     | SYS-TC-009  |
| SYS-REQ-010   | SWE-REQ-010                | Position Feedback Processing  | code/inc/position_feedback.h          | PF_TC_04     | SYS-TC-009  |
| SYS-REQ-011   | SWE-REQ-001                | Command Interface             | code/inc/command_interface.h,<br>code/src/command_interface.c | CI_TC_01   | SYS-TC-003  |
| SYS-REQ-012   | SWE-REQ-002                | Command Interface             | code/inc/command_interface.h,<br>code/src/command_interface.c | CI_TC_02   | SYS-TC-005  |
| SYS-REQ-013   | SWE-REQ-003                | Command Interface             | code/inc/command_interface.h          | CI_TC_03     | SYS-TC-007  |
| SYS-REQ-014   | SWE-REQ-013                | Status Indication             | code/inc/status_indication.h,<br>code/src/status_indication.c | NOT TRACED   | SYS-TC-001, SYS-TC-011 |
| SYS-REQ-015   | SWE-REQ-014                | Status Indication             | code/inc/status_indication.h,<br>code/src/status_indication.c | NOT TRACED   | SYS-TC-011, SYS-TC-012 |
| SYS-REQ-016   | SWE-REQ-014                | Status Indication             | code/inc/status_indication.h          | NOT TRACED   | SYS-TC-011  |
| SYS-REQ-017   | SWE-REQ-015                | Status Indication             | code/inc/status_indication.h          | NOT TRACED   | SYS-TC-011  |
| SYS-REQ-018   | SWE-REQ-021                | Control Logic                 | code/inc/control_logic.h,<br>code/src/control_logic.c | NOT TRACED   | SYS-TC-001  |
| SYS-REQ-019   | SWE-REQ-022                | Control Logic                 | code/inc/control_logic.h              | NOT TRACED   | SYS-TC-001, SYS-TC-002 |
| SYS-REQ-020   | SWE-REQ-023                | Control Logic                 | code/inc/control_logic.h              | NOT TRACED   | SYS-TC-006  |
| SYS-REQ-021   | SWE-REQ-024                | Control Logic                 | code/inc/control_logic.h              | NOT TRACED   | SYS-TC-012  |
| SYS-REQ-022   | SWE-REQ-024                | Control Logic                 | code/inc/control_logic.h              | NOT TRACED   | SYS-TC-012  |
| SYS-REQ-023   | SWE-REQ-025                | Control Logic, Command Interface | code/inc/control_logic.h,<br>code/inc/command_interface.h | CI_TC_04     | SYS-TC-005  |
| SYS-REQ-024   | SWE-REQ-016                | Command Interface             | code/inc/command_interface.h          | NOT TRACED   | NOT TRACED  |
| SYS-REQ-025   | SWE-REQ-017                | Flap Movement/Motor Control   | code/inc/flap_motor_control.h         | NOT TRACED   | NOT TRACED  |
| SYS-REQ-026   | SWE-REQ-018                | Position Feedback Processing  | code/inc/position_feedback.h          | NOT TRACED   | NOT TRACED  |
| SYS-REQ-027   | SWE-REQ-019                | Flap Movement/Motor Control   | code/inc/flap_motor_control.h         | NOT TRACED   | NOT TRACED  |
| SYS-REQ-028   | SWE-REQ-020                | Calibration Data Handler      | code/inc/calibration_data.h,<br>code/src/calibration_data.c | NOT TRACED   | NOT TRACED  |
| SYS-REQ-029   | SWE-REQ-028                | Calibration Data Handler      | code/inc/calibration_data.h           | NOT TRACED   | NOT TRACED  |
| SYS-REQ-030   | SWE-REQ-029                | Calibration Data Handler      | code/inc/calibration_data.h           | NOT TRACED   | NOT TRACED  |
| SYS-REQ-031   | SWE-REQ-033                | Command Interface             | code/inc/command_interface.h          | NOT TRACED   | NOT TRACED  |
| SYS-REQ-032   | SWE-REQ-030                | Error Handler                 | code/inc/error_handler.h,<br>code/src/error_handler.c | NOT TRACED   | SYS-TC-006  |
| SYS-REQ-033   | SWE-REQ-032                | Error Handler                 | code/inc/error_handler.h,<br>code/src/error_handler.c | NOT TRACED   | NOT TRACED  |
| SYS-REQ-034   | SWE-REQ-032                | Error Handler                 | code/inc/error_handler.h              | NOT TRACED   | SYS-TC-008  |
| SYS-REQ-035   | SWE-REQ-035                | N/A                          | N/A                                  | NOT TRACED   | NOT TRACED  |
| SYS-REQ-036   | SWE-REQ-036                | N/A                          | N/A                                  | NOT TRACED   | NOT TRACED  |
| SYS-REQ-037   | SWE-REQ-037                | N/A                          | N/A                                  | NOT TRACED   | NOT TRACED  |

### C) Backward Trace Matrix
| ST          | UT          | Code           | Unit                      | SWE           | SYS           |
|-------------|-------------|----------------|---------------------------|---------------|--------------|
| SYS-TC-001  | NOT TRACED  | code/inc/status_indication.h,<br>code/src/status_indication.c | Status Indication             | SWE-REQ-013       | SYS-REQ-014, SYS-REQ-018, SYS-REQ-019 |
| SYS-TC-002  | NOT TRACED  | code/inc/position_feedback.h,<br>code/src/position_feedback.c | Position Feedback Processing     | SWE-REQ-010, SWE-REQ-011  | SYS-REQ-008, SYS-REQ-019 |
| SYS-TC-003  | CI_TC_01    | code/inc/command_interface.h,<br>code/src/command_interface.c | Command Interface                 | SWE-REQ-001, SWE-REQ-005 | SYS-REQ-001, SYS-REQ-002, SYS-REQ-011 |
| SYS-TC-004  | NOT TRACED  | code/inc/command_interface.h,<br>code/src/command_interface.c | Command Interface              | SWE-REQ-003, SWE-REQ-006  | SYS-REQ-003, SYS-REQ-005 |
| SYS-TC-005  | CI_TC_02, CI_TC_04 | code/inc/command_interface.h,<br>code/src/command_interface.c,<br>code/inc/control_logic.h | Command Interface, Control Logic | SWE-REQ-002, SWE-REQ-025, SWE-REQ-031 | SYS-REQ-012, SYS-REQ-023 |
| SYS-TC-006  | NOT TRACED  | code/inc/error_handler.h,<br>code/src/error_handler.c  | Error Handler                     | SWE-REQ-030     | SYS-REQ-020, SYS-REQ-032 |
| SYS-TC-007  | NOT TRACED  | code/inc/command_interface.h     | Command Interface | SWE-REQ-003      | SYS-REQ-013 |
| SYS-TC-008  | NOT TRACED  | code/inc/error_handler.h         | Error Handler    | SWE-REQ-032      | SYS-REQ-034 |
| SYS-TC-009  | NOT TRACED  | code/inc/position_feedback.h     | Position Feedback Processing | SWE-REQ-010, SWE-REQ-011 | SYS-REQ-009, SYS-REQ-010 |
| SYS-TC-010  | NOT TRACED  | code/inc/flap_motor_control.h    | Flap Movement/Motor Control | SWE-REQ-008, SWE-REQ-009 | SYS-REQ-005, SYS-REQ-006 |
| SYS-TC-011  | NOT TRACED  | code/inc/status_indication.h     | Status Indication | SWE-REQ-014, SWE-REQ-015      | SYS-REQ-014, SYS-REQ-015, SYS-REQ-016, SYS-REQ-017 |
| SYS-TC-012  | CI_TC_01, CI_TC_03 | code/inc/command_interface.h,<br>code/src/command_interface.c,<br>code/inc/control_logic.h | Command Interface, Control Logic | SWE-REQ-001, SWE-REQ-003, SWE-REQ-024 | SYS-REQ-001, SYS-REQ-002, SYS-REQ-003, SYS-REQ-021, SYS-REQ-022, SYS-REQ-015 |

### D) Coverage Gaps

#### SYS without ST
- SYS-REQ-004, SYS-REQ-007, SYS-REQ-024, SYS-REQ-025, SYS-REQ-026, SYS-REQ-027, SYS-REQ-028, SYS-REQ-029, SYS-REQ-030, SYS-REQ-031, SYS-REQ-033, SYS-REQ-035, SYS-REQ-036, SYS-REQ-037

#### SWE without UT
- SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-007, SWE-REQ-008, SWE-REQ-009, SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-015, SWE-REQ-017, SWE-REQ-018, SWE-REQ-019, SWE-REQ-020, SWE-REQ-021, SWE-REQ-022, SWE-REQ-023, SWE-REQ-024, SWE-REQ-026, SWE-REQ-027, SWE-REQ-028, SWE-REQ-029, SWE-REQ-030, SWE-REQ-032, SWE-REQ-033, SWE-REQ-034, SWE-REQ-035, SWE-REQ-036, SWE-REQ-037, SWE-REQ-038

#### SWE without Code
- SWE-REQ-004, SWE-REQ-007, SWE-REQ-012, SWE-REQ-015, SWE-REQ-020, SWE-REQ-022, SWE-REQ-023, SWE-REQ-026, SWE-REQ-028, SWE-REQ-029, SWE-REQ-034, SWE-REQ-036, SWE-REQ-038

#### Orphan Tests (UT/ST not mapped)
- None detected; all test cases map to at least one requirement ID.

#### Orphan Code Files
- code/src/main.c (no direct requirement mapping)

---

(End of Traceability Report: All matrices and rows are complete. No truncation or summarization performed. If any rows above are missing, report PUSH_FAILED: TRACE_ROW_COUNT_MISMATCH.)
