## Traceability Report: HVAC Flap Actuator System (Branch: pref-162a)

---

## A) Summary Metrics

| Artifact                | Count |
|-------------------------|-------|
| System Requirements     | 35    |
| Software Requirements   | 40    |
| SW Units (ARCH/LLD)     | 6     |
| Code Files              | 12    |
| UT Cases                | 23    |
| ST Cases                | 11    |

| Covered by Next Level   | Coverage Percent |
|------------------------ |-----------------|
| SYS → SWE               | 34/35 = 97%     |
| SWE → Unit              | 39/40 = 98%     |
| Unit → Code File        | 6/6 = 100%      |
| SWE → UT                | 24/40 = 60%     |
| SYS → ST                | 22/35 = 63%     |
| SWE → ST                | 17/40 = 43%     |

---

## B) Forward Trace Matrix

| SYS-REQ | SWE-REQ | SW Unit | Code File | UT | ST |
|---------|---------|---------|-----------|----|----|
| SYS-REQ-001 | SWE-REQ-001,005 | UART Command Handler, Flap Actuator Controller | code/inc/uart_command_handler.h, code/inc/flap_actuator_controller.h, ... | UTC-1-01, UTC-2-02 | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-002 | SWE-REQ-001,006 | UART Command Handler, Flap Actuator Controller | code/inc/uart_command_handler.h, code/inc/flap_actuator_controller.h, ... | UTC-1-01, UTC-2-02 | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-003 | SWE-REQ-007,025 | Flap Actuator Controller | code/inc/flap_actuator_controller.h | UTC-2-03 | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-004 | SWE-REQ-002,031 | UART Command Handler, Flap Actuator Controller | code/inc/uart_command_handler.h, code/inc/flap_actuator_controller.h | UTC-1-02, UTC-2-04 | SYS-TC-004 |
| SYS-REQ-005 | SWE-REQ-008 | Motor Control Unit | code/inc/motor_control_unit.h | UTC-3-01 | SYS-TC-008 |
| SYS-REQ-006 | SWE-REQ-008,009 | Motor Control Unit | code/inc/motor_control_unit.h | UTC-3-01 | SYS-TC-008 |
| SYS-REQ-007 | SWE-REQ-010 | Motor Control Unit | code/inc/motor_control_unit.h | UTC-3-02 | SYS-TC-008 |
| SYS-REQ-008 | SWE-REQ-011 | Position Monitoring Unit | code/inc/position_monitoring_unit.h | UTC-4-01 | SYS-TC-007 |
| SYS-REQ-009 | SWE-REQ-012 | Position Monitoring Unit | code/inc/position_monitoring_unit.h | | SYS-TC-007, SYS-TC-011 |
| SYS-REQ-010 | SWE-REQ-011 | Position Monitoring Unit | code/inc/position_monitoring_unit.h | UTC-4-01 | SYS-TC-007, SYS-TC-011 |
| SYS-REQ-011 | SWE-REQ-013,032 | Position Monitoring Unit | code/inc/position_monitoring_unit.h | UTC-4-02, UTC-4-03 | SYS-TC-005 |
| SYS-REQ-012 | SWE-REQ-001,017 | UART Command Handler | code/inc/uart_command_handler.h | UTC-1-01, UTC-1-04 | NOT TRACED |
| SYS-REQ-013 | SWE-REQ-003,032 | UART Command Handler, Position Monitoring Unit | ... | UTC-1-03, UTC-4-03 | SYS-TC-004 |
| SYS-REQ-014 | SWE-REQ-014 | LED Indication | code/inc/led_indication.h | UTC-5-01 | SYS-TC-009 |
| SYS-REQ-015 | SWE-REQ-015,025 | LED Indication, Flap Actuator Controller | code/inc/led_indication.h, code/inc/flap_actuator_controller.h | UTC-5-02, UTC-2-03 | SYS-TC-002, SYS-TC-010, SYS-TC-011 |
| SYS-REQ-016 | SWE-REQ-016 | LED Indication | code/inc/led_indication.h | UTC-5-03 | SYS-TC-010, SYS-TC-011 |
| SYS-REQ-017 | SWE-REQ-014,021 | System Initialization, LED Indication | code/inc/system_initialization.h, code/inc/led_indication.h | UTC-6-01, UTC-5-01 | SYS-TC-001 |
| SYS-REQ-018 | SWE-REQ-021 | System Initialization | code/inc/system_initialization.h | UTC-6-01 | SYS-TC-001 |
| SYS-REQ-019 | SWE-REQ-011,022 | System Initialization, Position Monitoring Unit | ... | UTC-6-02, UTC-4-01 | SYS-TC-001, SYS-TC-002 |
| SYS-REQ-020 | SWE-REQ-023 | Flap Actuator Controller | code/inc/flap_actuator_controller.h | UTC-2-03 | SYS-TC-011 |
| SYS-REQ-021 | SWE-REQ-026 | Flap Actuator Controller | code/inc/flap_actuator_controller.h | UTC-2-04 | SYS-TC-004 |
| ... | ... | ... | ... | ... | ... |

_"NOT TRACED" indicates no direct next-level mapping found._

---

## C) Backward Trace Matrix (Selected Rows)

| ST Case      | UT(s)       | Code File(s)           | SW Unit(s)             | SWE-REQ(s)           | SYS-REQ(s)          |
|--------------|-------------|------------------------|------------------------|----------------------|---------------------|
| SYS-TC-003   | UTC-1-01, UTC-2-02 | code/inc/uart_command_handler.h, code/inc/flap_actuator_controller.h | UART Command Handler, Flap Actuator Controller | SWE-REQ-001,005,006 | SYS-REQ-001,002,003 |
| SYS-TC-011   | UTC-2-02, UTC-2-03  | code/inc/flap_actuator_controller.h | Flap Actuator Controller | SWE-REQ-005,006,025 | SYS-REQ-001,002,003,015,016,020,035 |
| SYS-TC-004   | UTC-1-02, UTC-2-04  | code/inc/uart_command_handler.h, code/inc/flap_actuator_controller.h | UART Command Handler, Flap Actuator Controller | SWE-REQ-002,031 | SYS-REQ-004,013,021 |
| SYS-TC-008   | UTC-3-01, UTC-3-02  | code/inc/motor_control_unit.h | Motor Control Unit | SWE-REQ-008,009,010 | SYS-REQ-005,006,007 |
| SYS-TC-009   | UTC-5-01            | code/inc/led_indication.h | LED Indication | SWE-REQ-014 | SYS-REQ-014 |

_(Refer to forward trace matrix for more details)_

---

## D) Coverage Gaps

### 1. SYS Requirements without Mapped ST
- SYS-REQ-012, SYS-REQ-027, SYS-REQ-028, SYS-REQ-033, ... (other entries where ``NOT TRACED`` in ST)

### 2. SWE Requirements without UT
- SWE-REQ-022, SWE-REQ-034, SWE-REQ-040, ...

### 3. SWE Requirements without Code
- SWE-REQ-040, SWE-REQ-036

### 4. Orphan UT Cases
- None detected. All UTs map to at least one SWE-REQ.

### 5. Orphan Code Files
- None detected. All code files map to a SW unit and requirement.

---

_(End of Traceability Report)_
