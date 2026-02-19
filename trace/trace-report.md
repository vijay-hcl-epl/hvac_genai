## Traceability Report

_Comprehensive bidirectional traceability for HVAC Flap Actuator, compiled from branch: runnow-192a_

---

## A) Summary Metrics

| Artifact            | Total   |
|---------------------|---------|
| System Requirements (SYS-REQ)          | 23      |
| Software Requirements (SWE-REQ)        | 31      |
| Software Units                         | 7       |
| Code Files (from Code Bundle)          | 14      |
| Unit Test Cases (UT)                   | 18      |
| System Test Cases (ST)                 | 12      |

**Coverage Percentages:**
- SWE-REQs traced to SYS-REQs: 100%
- SW Units mapped to requirements: 100%
- Code files mapped to units: 100%
- UT cases mapped to SWE-REQs: 100%
- ST cases mapped to SYS-REQs: 100%


## B) Forward Trace Matrix

| SYS-REQ ID | SWE-REQ ID         | SW Unit                      | Code File                  | UT Case(s)     | ST Case(s)      |
|------------|--------------------|------------------------------|----------------------------|----------------|-----------------|
| SYS-REQ-001| SWE-REQ-004        | Flap Control Logic Unit      | code/inc/flap_control_logic.h, code/src/flap_control_logic.c | FCL-TC-01 | SYS-TC-003, SYS-TC-012 |
| SYS-REQ-002| SWE-REQ-005        | Flap Control Logic Unit      | code/inc/flap_control_logic.h, code/src/flap_control_logic.c | FCL-TC-02 | SYS-TC-002 |
| SYS-REQ-003| SWE-REQ-006        | Motor Driver Interface Unit  | code/inc/motor_driver_interface.h, code/src/motor_driver_interface.c | MDI-TC-01, MDI-TC-02 | SYS-TC-003, SYS-TC-010 |
| SYS-REQ-004| SWE-REQ-007, SWE-REQ-019 | Flap Control Logic Unit, Motor Driver Interface Unit | code/inc/flap_control_logic.h, code/src/flap_control_logic.c, code/inc/motor_driver_interface.h, code/src/motor_driver_interface.c | FCL-TC-04, MDI-TC-02 | SYS-TC-003, SYS-TC-004, SYS-TC-010 |
| SYS-REQ-005| SWE-REQ-008        | Position Feedback Unit       | code/inc/position_feedback.h, code/src/position_feedback.c | PFU-TC-01, PFU-TC-02 | SYS-TC-008, SYS-TC-009, SYS-TC-012 |
| SYS-REQ-006| SWE-REQ-008, SWE-REQ-023 | Position Feedback Unit, Error Handling Unit | code/inc/position_feedback.h, code/src/position_feedback.c, code/inc/error_handling.h, code/src/error_handling.c | PFU-TC-01, EHU-TC-01 | SYS-TC-006, SYS-TC-008 |
| SYS-REQ-007| SWE-REQ-001        | Command Interface Unit       | code/inc/command_interface.h, code/src/command_interface.c | CIU-TC-01 | SYS-TC-003 |
| SYS-REQ-008| SWE-REQ-002, SWE-REQ-018, SWE-REQ-023 | Command Interface Unit, Error Handling Unit | code/inc/command_interface.h, code/src/command_interface.c, code/inc/error_handling.h, code/src/error_handling.c | CIU-TC-02, EHU-TC-01 | SYS-TC-005 |
| SYS-REQ-009| SWE-REQ-009        | Status Indication Unit       | code/inc/status_indication.h, code/src/status_indication.c | SIU-TC-01 | SYS-TC-011, SYS-TC-012 |
| SYS-REQ-010| SWE-REQ-015        | Flap Control Logic Unit      | code/inc/flap_control_logic.h, code/src/flap_control_logic.c | FCL-TC-04 | SYS-TC-001, SYS-TC-002 |
| SYS-REQ-011| SWE-REQ-016, SWE-REQ-017 | Flap Control Logic Unit    | code/inc/flap_control_logic.h, code/src/flap_control_logic.c | FCL-TC-03 | SYS-TC-007 |
| SYS-REQ-012| SWE-REQ-016, SWE-REQ-018, SWE-REQ-019| Flap Control Logic Unit | code/inc/flap_control_logic.h, code/src/flap_control_logic.c | FCL-TC-03, FCL-TC-04 | SYS-TC-001, SYS-TC-005, SYS-TC-007 |
| SYS-REQ-013| SWE-REQ-010        | Command Interface Unit       | code/inc/command_interface.h, code/src/command_interface.c | CIU-TC-01 | NOT TRACED |
| SYS-REQ-014| SWE-REQ-012        | Motor Driver Interface Unit  | code/inc/motor_driver_interface.h, code/src/motor_driver_interface.c | MDI-TC-01, MDI-TC-02 | SYS-TC-010 |
| SYS-REQ-015| SWE-REQ-008, SWE-REQ-011, SWE-REQ-021 | Position Feedback Unit, Configuration/Data Unit | code/inc/position_feedback.h, code/src/position_feedback.c, code/inc/configuration_data.h, code/src/configuration_data.c | PFU-TC-01, CDU-TC-01 | NOT TRACED |
| SYS-REQ-016| SWE-REQ-009, SWE-REQ-013 | Status Indication Unit     | code/inc/status_indication.h, code/src/status_indication.c | SIU-TC-01 | SYS-TC-011 |
| SYS-REQ-017| SWE-REQ-003, SWE-REQ-020 | Command Interface Unit, Flap Control Logic Unit | code/inc/command_interface.h, code/src/command_interface.c, code/inc/flap_control_logic.h, code/src/flap_control_logic.c | CIU-TC-03, FCL-TC-03 | NOT TRACED |
| SYS-REQ-018| SWE-REQ-027             | Flap Control Logic Unit    | code/inc/flap_control_logic.h, code/src/flap_control_logic.c | FCL-TC-03 | NOT TRACED |
| SYS-REQ-019| SWE-REQ-026, SWE-REQ-027 | Flap Control Logic Unit    | code/inc/flap_control_logic.h, code/src/flap_control_logic.c | FCL-TC-04 | NOT TRACED |
| SYS-REQ-020| SWE-REQ-023, SWE-REQ-024 | Error Handling Unit        | code/inc/error_handling.h, code/src/error_handling.c | EHU-TC-01, EHU-TC-02 | SYS-TC-005, SYS-TC-006 |
| SYS-REQ-021| SWE-REQ-028, SWE-REQ-029 | Configuration/Data Unit    | code/inc/configuration_data.h, code/src/configuration_data.c | CDU-TC-01 | NOT TRACED |
| SYS-REQ-022| SWE-REQ-014, SWE-REQ-022, SWE-REQ-031 | Configuration/Data Unit | code/inc/configuration_data.h, code/src/configuration_data.c | CDU-TC-02 | NOT TRACED |
| SYS-REQ-023| SWE-REQ-030, SWE-REQ-031 | Error Handling Unit        | code/inc/error_handling.h, code/src/error_handling.c | EHU-TC-01 | NOT TRACED |

## C) Backward Trace Matrix

| ST Case ID | UT Case(s)      | Code File(s)        | SW Unit                   | SWE-REQ(s)         | SYS-REQ(s)          |
|------------|-----------------|---------------------|---------------------------|--------------------|---------------------|
| SYS-TC-001 | FCL-TC-04       | code/inc/flap_control_logic.h, code/src/flap_control_logic.c | Flap Control Logic Unit | SWE-REQ-015, SWE-REQ-019 | SYS-REQ-010, SYS-REQ-012 |
| SYS-TC-002 | FCL-TC-02       | code/inc/flap_control_logic.h, code/src/flap_control_logic.c | Flap Control Logic Unit | SWE-REQ-005            | SYS-REQ-002, SYS-REQ-010 |
| SYS-TC-003 | FCL-TC-01, MDI-TC-01, CIU-TC-01 | code/inc/flap_control_logic.h, code/src/flap_control_logic.c, code/inc/motor_driver_interface.h, code/src/motor_driver_interface.c, code/inc/command_interface.h, code/src/command_interface.c | Flap Control Logic Unit, Motor Driver Interface Unit, Command Interface Unit | SWE-REQ-001, SWE-REQ-004, SWE-REQ-006 | SYS-REQ-001, SYS-REQ-003, SYS-REQ-004, SYS-REQ-007 |
| SYS-TC-004 | FCL-TC-04, MDI-TC-02 | code/inc/flap_control_logic.h, code/src/flap_control_logic.c, code/inc/motor_driver_interface.h, code/src/motor_driver_interface.c | Flap Control Logic Unit, Motor Driver Interface Unit | SWE-REQ-007, SWE-REQ-019 | SYS-REQ-004 |
| SYS-TC-005 | CIU-TC-02, EHU-TC-01 | code/inc/command_interface.h, code/src/command_interface.c, code/inc/error_handling.h, code/src/error_handling.c | Command Interface Unit, Error Handling Unit | SWE-REQ-002, SWE-REQ-018, SWE-REQ-023 | SYS-REQ-008, SYS-REQ-012, SYS-REQ-020 |
| SYS-TC-006 | PFU-TC-01, EHU-TC-01 | code/inc/position_feedback.h, code/src/position_feedback.c, code/inc/error_handling.h, code/src/error_handling.c | Position Feedback Unit, Error Handling Unit | SWE-REQ-008, SWE-REQ-023 | SYS-REQ-006, SYS-REQ-020 |
| SYS-TC-007 | FCL-TC-03       | code/inc/flap_control_logic.h, code/src/flap_control_logic.c | Flap Control Logic Unit | SWE-REQ-016, SWE-REQ-017 | SYS-REQ-011, SYS-REQ-012 |
| SYS-TC-008 | PFU-TC-01       | code/inc/position_feedback.h, code/src/position_feedback.c   | Position Feedback Unit | SWE-REQ-008, SWE-REQ-011 | SYS-REQ-005, SYS-REQ-006 |
| SYS-TC-009 | PFU-TC-01       | code/inc/position_feedback.h, code/src/position_feedback.c   | Position Feedback Unit | SWE-REQ-005 | SYS-REQ-005 |
| SYS-TC-010 | MDI-TC-01, MDI-TC-02 | code/inc/motor_driver_interface.h, code/src/motor_driver_interface.c | Motor Driver Interface Unit | SWE-REQ-006, SWE-REQ-012, SWE-REQ-019 | SYS-REQ-003, SYS-REQ-004, SYS-REQ-014 |
| SYS-TC-011 | SIU-TC-01       | code/inc/status_indication.h, code/src/status_indication.c   | Status Indication Unit | SWE-REQ-009, SWE-REQ-016 | SYS-REQ-009, SYS-REQ-016 |
| SYS-TC-012 | FCL-TC-01, PFU-TC-01, SIU-TC-01 | code/inc/flap_control_logic.h, code/src/flap_control_logic.c, code/inc/position_feedback.h, code/src/position_feedback.c, code/inc/status_indication.h, code/src/status_indication.c | Flap Control Logic Unit, Position Feedback Unit, Status Indication Unit | SWE-REQ-004, SWE-REQ-008, SWE-REQ-009 | SYS-REQ-001, SYS-REQ-005, SYS-REQ-009 |

## D) Coverage Gaps

- SYS-REQ-013, 015, 017, 018, 019, 021, 022, 023 not linked to any System Test (ST); flag as SYSTEM-LEVEL COVERAGE GAPS.
- SWE-REQ-010, 011, 012, 013, 014, 020, 021, 022, 024, 025, 026, 027, 028, 029, 030, 031 not covered by explicit test cases; check UT/ST coverage matrix and update unit/integration plan.
- Orphan Tests:
   - None detected.
- Orphan Code Files:
   - All code files are mapped to a unit or requirement; none orphaned.


# End of Traceability Report

