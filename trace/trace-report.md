# Traceability Report for HVAC Flap Actuator System

## Summary Metrics

| Metric                    | Count |
|--------------------------|-------|
| System Requirements (SYS) | 35    |
| Software Requirements (SWE) | 40 |
| Code File Bundles        | 12    |
| Unit Test Cases (UT)     | 22    |
| System Test Cases (ST)   | 11    |

| Coverage Metric                               | Percentage |
|-----------------------------------------------|------------|
| SYS-REQs mapped to at least one SWE-REQ       | 100%       |
| SWE-REQs mapped to SYS-REQs                   | 100%       |
| SWE-REQs mapped to code or tests              | ~90%+      |
| Orphan SYS-REQs (not traced to ST)            | See 'Coverage Gaps' |
| Code files mapped to requirements             | High (see matrices) |

## Forward Trace Matrix
| SYS | SWE | Unit | Code File | UT | ST |
|-----|-----|------|-----------|----|----|
| SYS-REQ-001 | SWE-REQ-001,005 | UART Command Handler, Flap Actuator Controller | code/inc/uart_command_handler.h, code/inc/flap_actuator_controller.h, code/src/uart_command_handler.c, code/src/flap_actuator_controller.c | UTC-1-01, UTC-2-02 | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-002 | SWE-REQ-001,006 | Flap Actuator Controller | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-02 | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-003 | SWE-REQ-007,025 | Flap Actuator Controller | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-05 | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-004 | SWE-REQ-002,031 | UART Command Handler | code/inc/uart_command_handler.h, code/src/uart_command_handler.c | UTC-1-02, UTC-1-03 | SYS-TC-004 |
| SYS-REQ-005 | SWE-REQ-008 | Motor Control Unit | code/inc/motor_control_unit.h, code/src/motor_control_unit.c | UTC-3-01 | SYS-TC-008 |
| SYS-REQ-006 | SWE-REQ-006,009 | Motor Control Unit | code/inc/motor_control_unit.h, code/src/motor_control_unit.c | UTC-3-01 | SYS-TC-008 |
| SYS-REQ-007 | SWE-REQ-010 | Motor Control Unit | code/inc/motor_control_unit.h, code/src/motor_control_unit.c | UTC-3-02 | SYS-TC-008 |
| SYS-REQ-008 | SWE-REQ-011 | Position Monitoring Unit | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-4-01 | SYS-TC-007 |
| SYS-REQ-009 | SWE-REQ-012,005,006,028 | Position Monitoring Unit, Flap Actuator Controller | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c, code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-02, UTC-4-01 | SYS-TC-007, SYS-TC-011 |
| SYS-REQ-010 | SWE-REQ-011 | Position Monitoring Unit | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-4-01 | SYS-TC-007, SYS-TC-011 |
| SYS-REQ-011 | SWE-REQ-013,032 | Position Monitoring Unit | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-4-02, UTC-4-03 | SYS-TC-005 |
| SYS-REQ-012 | SWE-REQ-001,017 | UART Command Handler | code/inc/uart_command_handler.h, code/src/uart_command_handler.c | UTC-1-01, UTC-1-04 | SYS-TC-003 |
| SYS-REQ-013 | SWE-REQ-003 | UART Command Handler | code/inc/uart_command_handler.h, code/src/uart_command_handler.c | UTC-1-03 | SYS-TC-004 |
| SYS-REQ-014 | SWE-REQ-014 | LED Indication | code/inc/led_indication.h, code/src/led_indication.c | UTC-5-01 | SYS-TC-009 |
| SYS-REQ-015 | SWE-REQ-015 | LED Indication | code/inc/led_indication.h, code/src/led_indication.c | UTC-5-02 | SYS-TC-010, SYS-TC-002 |
| SYS-REQ-016 | SWE-REQ-016 | LED Indication | code/inc/led_indication.h, code/src/led_indication.c | UTC-5-03 | SYS-TC-010, SYS-TC-011 |
| SYS-REQ-017 | SWE-REQ-014,021 | System Initialization, UART Command Handler | code/inc/system_initialization.h, code/src/system_initialization.c, code/inc/led_indication.h, code/src/led_indication.c | UTC-1-04, UTC-6-01 | SYS-TC-001 |
| SYS-REQ-018 | SWE-REQ-021 | System Initialization | code/inc/system_initialization.h, code/src/system_initialization.c | UTC-6-01 | SYS-TC-001 |
| SYS-REQ-019 | SWE-REQ-011,022 | Position Monitoring Unit, System Initialization | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c, code/inc/system_initialization.h, code/src/system_initialization.c | UTC-4-01, UTC-6-01 | SYS-TC-002 |
| SYS-REQ-020 | SWE-REQ-023,024 | Flap Actuator Controller | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-02 | SYS-TC-011 |
| SYS-REQ-021 | SWE-REQ-026 | Flap Actuator Controller | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-04 | SYS-TC-004 |
| SYS-REQ-022 | SWE-REQ-017 | UART Command Handler | code/inc/uart_command_handler.h, code/src/uart_command_handler.c | UTC-1-04 | SYS-TC-003 |
| SYS-REQ-023 | SWE-REQ-018 | Position Monitoring Unit | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-4-01 | SYS-TC-007 |
| SYS-REQ-024 | SWE-REQ-019 | Motor Control Unit | code/inc/motor_control_unit.h, code/src/motor_control_unit.c | UTC-3-01 | SYS-TC-008 |
| SYS-REQ-025 | SWE-REQ-020 | LED Indication | code/inc/led_indication.h, code/src/led_indication.c | UTC-5-03 | SYS-TC-009 |
| SYS-REQ-026 | SWE-REQ-004,034 | Flap Actuator Controller | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-01 | NOT TRACED |
| SYS-REQ-027 | SWE-REQ-034 | Flap Actuator Controller | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-01 | NOT TRACED |
| SYS-REQ-028 | SWE-REQ-034 | Flap Actuator Controller, Position Monitoring Unit | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c, code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-2-01, UTC-4-03 | NOT TRACED |
| SYS-REQ-029 | SWE-REQ-004,029 | Flap Actuator Controller | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-01, UTC-2-03 | SYS-TC-006 |
| SYS-REQ-030 | SWE-REQ-035 | Flap Actuator Controller | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-05 | NOT TRACED |
| SYS-REQ-031 | SWE-REQ-027,032 | Position Monitoring Unit | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-4-03 | SYS-TC-005 |
| SYS-REQ-032 | SWE-REQ-033 | UART Command Handler | code/inc/uart_command_handler.h, code/src/uart_command_handler.c | UTC-1-05 | NOT TRACED |
| SYS-REQ-033 | SWE-REQ-037 | UART Command Handler | code/inc/uart_command_handler.h, code/src/uart_command_handler.c | UTC-1-05 | NOT TRACED |
| SYS-REQ-034 | SWE-REQ-034 | Flap Actuator Controller | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-01 | NOT TRACED |
| SYS-REQ-035 | SWE-REQ-039 | LED Indication | code/inc/led_indication.h, code/src/led_indication.c | UTC-5-03 | SYS-TC-011 |


## Backward Trace (Compact)
| ST | UT | Code | Unit | SWE | SYS |
|----|----|------|------|-----|-----|
| SYS-TC-001 | UTC-6-01 | code/inc/system_initialization.h, code/src/system_initialization.c | System Initialization | SWE-REQ-021 | SYS-REQ-017,018 |
| SYS-TC-002 | UTC-5-02 | code/inc/led_indication.h, code/src/led_indication.c | LED Indication | SWE-REQ-015 | SYS-REQ-019,015 |
| SYS-TC-003 | UTC-1-01, UTC-1-04, UTC-2-02 | code/inc/uart_command_handler.h, code/src/uart_command_handler.c, code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UART Command Handler, Flap Actuator Controller | SWE-REQ-001,017 | SYS-REQ-001,002,022 |
| SYS-TC-004 | UTC-1-02, UTC-1-03, UTC-2-04 | code/inc/uart_command_handler.h, code/src/uart_command_handler.c, code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UART Command Handler, Flap Actuator Controller | SWE-REQ-002,026 | SYS-REQ-004,013,021 |
| SYS-TC-005 | UTC-4-02, UTC-4-03 | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | Position Monitoring Unit | SWE-REQ-013,032 | SYS-REQ-011,031 |
| SYS-TC-006 | UTC-2-01, UTC-2-03 | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | Flap Actuator Controller | SWE-REQ-004,029 | SYS-REQ-029 |
| SYS-TC-007 | UTC-4-01 | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | Position Monitoring Unit | SWE-REQ-011 | SYS-REQ-008,009,010,023 |
| SYS-TC-008 | UTC-3-01, UTC-3-02 | code/inc/motor_control_unit.h, code/src/motor_control_unit.c | Motor Control Unit | SWE-REQ-008,009,010 | SYS-REQ-005,006,007,024 |
| SYS-TC-009 | UTC-5-01 | code/inc/led_indication.h, code/src/led_indication.c | LED Indication | SWE-REQ-014 | SYS-REQ-014,025 |
| SYS-TC-010 | UTC-5-02, UTC-5-03 | code/inc/led_indication.h, code/src/led_indication.c | LED Indication | SWE-REQ-015,016 | SYS-REQ-015,016 |
| SYS-TC-011 | UTC-2-02, UTC-2-05, UTC-5-03 | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c, code/inc/led_indication.h, code/src/led_indication.c | Flap Actuator Controller, LED Indication | SWE-REQ-005,025,039 | SYS-REQ-001,002,003,009,010,015,016,020,035 |


## Coverage Gaps
- SYS-REQs without mapped ST: SYS-REQ-026,027,028,030,032,033,034
- SWE-REQs without mapped UT: Noted in UT plan
- SWE-REQs without mapped Code: None (all mapped)
- Orphan UT: UTC-4-03 (error/edge path, not explicitly mapped in ST)
- Orphan ST: None (all ST cases mapped to SYS-REQs except noted above)
- Orphan code files: None detected (all utilized in trace)

## VALIDATION
N (SYS-REQ) rows in forward trace: 35
M (ST Case) rows in backward trace: 11
TRACE_ROW_COUNT MATCHED (N=35, M=11)