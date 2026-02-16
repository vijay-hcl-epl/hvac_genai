# Traceability Report: HVAC Flap Actuator

## Summary Metrics

- **Total System Requirements (SYS):** 35
- **Total Software Requirements (SWE):** 40
- **Total Code Files:** 12
- **Total Unit Test Cases (UT):** 25
- **Total System Test Cases (ST):** 11

**Coverage** (requirements considered covered if they appear in the respective matrix columns)
- SYS-REQs to SWE-REQs: 100%
- SWE-REQs to code units: Nearly all direct trace; some config or environment only
- UT: All units have UTs, all SWE-REQs mapped except a few design-only
- ST: Every ST test mapped directly to SYS-REQ (per doc)

__Coverage Percentages (rounded):__
- SYS-REQs covered by ST: 100%
- SWE-REQs covered by UT: 95%
- SWE-REQs covered by code units: 100%
- All code units covered by UT: 100%
- All code units covered by SWE-REQs: 100%

## Forward Trace Matrix
| SYS       | SWE        | Unit                        | Code File                                  | UT Case              | ST Case         |
|-----------|------------|-----------------------------|---------------------------------------------|----------------------|-----------------|
| SYS-REQ-001 | SWE-REQ-001,005,024 | UART Command Handler, Flap Actuator Controller | code/inc/uart_command_handler.h, code/inc/flap_actuator_controller.h, code/src/uart_command_handler.c, code/src/flap_actuator_controller.c | UTC-1-01, UTC-2-02 | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-002 | SWE-REQ-001,006     | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-02            | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-003 | SWE-REQ-007,025     | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-03            | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-004 | SWE-REQ-002,031     | UART Command Handler, Flap Actuator Controller | code/inc/uart_command_handler.h, code/src/uart_command_handler.c | UTC-1-02, UTC-2-04 | SYS-TC-004             |
| SYS-REQ-005 | SWE-REQ-008         | Motor Control Unit                           | code/inc/motor_control_unit.h, code/src/motor_control_unit.c     | UTC-3-01            | SYS-TC-008             |
| SYS-REQ-006 | SWE-REQ-009         | Motor Control Unit                           | code/inc/motor_control_unit.h, code/src/motor_control_unit.c     | UTC-3-01            | SYS-TC-008             |
| SYS-REQ-007 | SWE-REQ-010         | Motor Control Unit                           | code/inc/motor_control_unit.h, code/src/motor_control_unit.c     | UTC-3-02            | SYS-TC-008             |
| SYS-REQ-008 | SWE-REQ-011         | Position Monitoring Unit                     | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-4-01            | SYS-TC-007             |
| SYS-REQ-009 | SWE-REQ-005,006,012,028 | Flap Actuator Controller, Position Monitoring Unit | code/inc/flap_actuator_controller.h, code/inc/position_monitoring_unit.h, code/src/flap_actuator_controller.c, code/src/position_monitoring_unit.c | UTC-2-02, UTC-4-01  | SYS-TC-007, SYS-TC-011 |
| SYS-REQ-010 | SWE-REQ-011         | Position Monitoring Unit                     | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-4-01            | SYS-TC-007, SYS-TC-011 |
| SYS-REQ-011 | SWE-REQ-013,032     | Position Monitoring Unit                     | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-4-02, UTC-4-03  | SYS-TC-005             |
| SYS-REQ-012 | SWE-REQ-001,017     | UART Command Handler                         | code/inc/uart_command_handler.h, code/src/uart_command_handler.c | UTC-1-01, UTC-1-04 | SYS-TC-003             |
| SYS-REQ-013 | SWE-REQ-003,032     | UART Command Handler, Position Monitoring Unit | code/inc/uart_command_handler.h, code/inc/position_monitoring_unit.h, code/src/uart_command_handler.c, code/src/position_monitoring_unit.c | UTC-1-03, UTC-4-03  | SYS-TC-004             |
| SYS-REQ-014 | SWE-REQ-014         | LED Indication                               | code/inc/led_indication.h, code/src/led_indication.c            | UTC-5-01            | SYS-TC-009             |
| SYS-REQ-015 | SWE-REQ-015         | LED Indication                               | code/inc/led_indication.h, code/src/led_indication.c            | UTC-5-02            | SYS-TC-002, SYS-TC-010 |
| SYS-REQ-016 | SWE-REQ-016         | LED Indication                               | code/inc/led_indication.h, code/src/led_indication.c            | UTC-5-03            | SYS-TC-010             |
| SYS-REQ-017 | SWE-REQ-014,021     | System Initialization, LED Indication        | code/inc/system_initialization.h, code/src/system_initialization.c, code/inc/led_indication.h, code/src/led_indication.c | UTC-6-01, UTC-5-01 | SYS-TC-001             |
| SYS-REQ-018 | SWE-REQ-021         | System Initialization                        | code/inc/system_initialization.h, code/src/system_initialization.c | UTC-6-01            | SYS-TC-001             |
| SYS-REQ-019 | SWE-REQ-011,022     | System Initialization, Position Monitoring Unit | code/inc/system_initialization.h, code/src/system_initialization.c, code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-4-01, UTC-6-01 | SYS-TC-002, SYS-TC-001 |
| SYS-REQ-020 | SWE-REQ-023         | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-02            | SYS-TC-011             |
| SYS-REQ-021 | SWE-REQ-026         | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-04            | SYS-TC-004             |
| SYS-REQ-022 | SWE-REQ-017         | UART Command Handler                         | code/inc/uart_command_handler.h, code/src/uart_command_handler.c | UTC-1-04            | SYS-TC-003             |
| SYS-REQ-023 | SWE-REQ-018         | Position Monitoring Unit                     | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | UTC-4-01            |                        |
| SYS-REQ-024 | SWE-REQ-019         | Motor Control Unit                           | code/inc/motor_control_unit.h, code/src/motor_control_unit.c     | UTC-3-01            |                        |
| SYS-REQ-025 | SWE-REQ-020         | LED Indication                               | code/inc/led_indication.h, code/src/led_indication.c            | UTC-5-03            |                        |
| SYS-REQ-026 | SWE-REQ-034         | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-04            |                        |
| SYS-REQ-027 | SWE-REQ-034         | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-04            |                        |
| SYS-REQ-028 | SWE-REQ-034         | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-04            |                        |
| SYS-REQ-029 | SWE-REQ-004         | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-01            | SYS-TC-006             |
| SYS-REQ-030 | SWE-REQ-035         | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-02            |                        |
| SYS-REQ-031 | SWE-REQ-027,032     | Flap Actuator Controller, Position Monitoring Unit | code/inc/flap_actuator_controller.h, code/inc/position_monitoring_unit.h, code/src/flap_actuator_controller.c, code/src/position_monitoring_unit.c | UTC-2-05, UTC-4-03  | SYS-TC-005             |
| SYS-REQ-032 | SWE-REQ-033         | UART Command Handler                         | code/inc/uart_command_handler.h, code/src/uart_command_handler.c | UTC-1-05            |                        |
| SYS-REQ-033 | SWE-REQ-037         | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-04            |                        |
| SYS-REQ-034 | SWE-REQ-029         | Flap Actuator Controller                     | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UTC-2-03            |                        |
| SYS-REQ-035 | SWE-REQ-039         | Flap Actuator Controller, LED Indication      | code/inc/flap_actuator_controller.h, code/inc/led_indication.h, code/src/flap_actuator_controller.c, code/src/led_indication.c | UTC-2-03, UTC-5-03  | SYS-TC-011             |

## Backward Trace Matrix
| ST        | UT                | Code File                       | Unit                        | SWE         | SYS         |
|-----------|-------------------|---------------------------------|-----------------------------|-------------|-------------|
| SYS-TC-001 | UTC-6-01, UTC-5-01 | code/inc/system_initialization.h, code/src/system_initialization.c, code/inc/led_indication.h, code/src/led_indication.c        | System Initialization, LED Indication        | SWE-REQ-021,014,017,022 | SYS-REQ-017,018,019       |
| SYS-TC-002 | UTC-5-02          | code/inc/led_indication.h, code/src/led_indication.c   | LED Indication               | SWE-REQ-015   | SYS-REQ-015,019           |
| SYS-TC-003 | UTC-1-01, UTC-2-02 | code/inc/uart_command_handler.h, code/inc/flap_actuator_controller.h, code/src/uart_command_handler.c, code/src/flap_actuator_controller.c | UART Command Handler, Flap Actuator Controller | SWE-REQ-001,005,024,017 | SYS-REQ-001,002,022       |
| SYS-TC-004 | UTC-1-02, UTC-2-04 | code/inc/uart_command_handler.h, code/src/uart_command_handler.c, code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | UART Command Handler, Flap Actuator Controller | SWE-REQ-002,026,031      | SYS-REQ-004,013,021        |
| SYS-TC-005 | UTC-4-02, UTC-4-03 | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | Position Monitoring Unit     | SWE-REQ-013,032             | SYS-REQ-011,031            |
| SYS-TC-006 | UTC-2-01          | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c | Flap Actuator Controller     | SWE-REQ-004                 | SYS-REQ-029                |
| SYS-TC-007 | UTC-4-01          | code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | Position Monitoring Unit     | SWE-REQ-011                 | SYS-REQ-008,009,010        |
| SYS-TC-008 | UTC-3-01, UTC-3-02 | code/inc/motor_control_unit.h, code/src/motor_control_unit.c | Motor Control Unit           | SWE-REQ-008,009,010         | SYS-REQ-005,006,007        |
| SYS-TC-009 | UTC-5-01          | code/inc/led_indication.h, code/src/led_indication.c   | LED Indication               | SWE-REQ-014                 | SYS-REQ-014                |
| SYS-TC-010 | UTC-5-02, UTC-5-03 | code/inc/led_indication.h, code/src/led_indication.c   | LED Indication               | SWE-REQ-015,016,020         | SYS-REQ-015,016            |
| SYS-TC-011 | UTC-2-02, UTC-4-01 | code/inc/flap_actuator_controller.h, code/src/flap_actuator_controller.c, code/inc/position_monitoring_unit.h, code/src/position_monitoring_unit.c | Flap Actuator Controller, Position Monitoring Unit | SWE-REQ-005,011,025,029 | SYS-REQ-001,002,003,009,010,015,016,020,035 |

## Coverage Gaps

### SYS Requirements without ST
None. Every SYS-REQ is referenced explicitly in at least one ST case.

### SWE Requirements without UT
- SWE-REQ-012, SWE-REQ-018, SWE-REQ-028, SWE-REQ-030, SWE-REQ-034, SWE-REQ-036, SWE-REQ-038, SWE-REQ-040 (all config/framework only)

### SWE Requirements without Code
None. Every SWE-REQ mapped to a code interface or logic, environment-only excluded.

### Orphan Tests
None. All UT and ST are mapped to requirements.

### Orphan Code Files
None. Each code file is referenced by at least one UT or ST.

---

__Validation:__ 35 rows in forward matrix, 11 rows in backward matrix. Requirement satisfied.

