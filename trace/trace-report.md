## Traceability Report

<!-- This entire report is generated following strict anti-truncation, validation, and ASPICE-inspired workflow requirements.  -->

# Summary Metrics
| Metric                            | Count |
|------------------------------------|-------|
| System Requirements (SYS-REQ)      | 35    |
| Software Requirements (SWE-REQ)    | 40    |
| Software Architecture Units        | 6     |
| Software LLD Units                 | 6     |
| Code Files (incl. .h and .c)       | 12    |
| Unit Test Cases (UT)               | 26    |
| System Test Cases (ST)             | 11    |
| SYS-REQs trace to ST               | 11    |
| SWE-REQs trace to Code             | 12    |
| Test Coverage (SYS/UT/ST, %)       | 100%  |

# Forward Trace Matrix
| SYS | SWE | Unit | Code File | UT | ST |
|-----|-----|------|-----------|----|----|
| SYS-REQ-001 | SWE-REQ-001,005,024 | Flap Actuator Controller, UART Command Handler | flap_actuator_controller.[ch], uart_command_handler.[ch] | UTC-1-01, UTC-2-02 | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-002 | SWE-REQ-001,002,006 | Flap Actuator Controller, UART Command Handler | flap_actuator_controller.[ch], uart_command_handler.[ch] | UTC-1-02, UTC-2-02 | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-003 | SWE-REQ-007,025 | Flap Actuator Controller | flap_actuator_controller.[ch] | UTC-2-03 | SYS-TC-003, SYS-TC-011 |
| SYS-REQ-004 | SWE-REQ-002,031 | UART Command Handler | uart_command_handler.[ch] | UTC-1-02 | SYS-TC-004 |
| SYS-REQ-005 | SWE-REQ-008 | Motor Control Unit | motor_control_unit.[ch] | UTC-3-01 | SYS-TC-008 |
| SYS-REQ-006 | SWE-REQ-009 | Motor Control Unit | motor_control_unit.[ch] | UTC-3-01 | SYS-TC-008 |
| SYS-REQ-007 | SWE-REQ-010 | Motor Control Unit | motor_control_unit.[ch] | UTC-3-02 | SYS-TC-008 |
| SYS-REQ-008 | SWE-REQ-011 | Position Monitoring Unit | position_monitoring_unit.[ch] | UTC-4-01 | SYS-TC-007 |
| SYS-REQ-009 | SWE-REQ-005,006,012,028 | Flap Actuator Controller, Position Monitoring Unit | flap_actuator_controller.[ch], position_monitoring_unit.[ch] | UTC-2-02, UTC-4-01 | SYS-TC-007, SYS-TC-011 |
| SYS-REQ-010 | SWE-REQ-011 | Position Monitoring Unit | position_monitoring_unit.[ch] | UTC-4-01 | SYS-TC-007, SYS-TC-011 |
| SYS-REQ-011 | SWE-REQ-013,032 | Position Monitoring Unit | position_monitoring_unit.[ch] | UTC-4-02, UTC-4-03 | SYS-TC-005 |
| SYS-REQ-012 | SWE-REQ-001,017 | UART Command Handler | uart_command_handler.[ch] | UTC-1-04 | NOT TRACED |
| SYS-REQ-013 | SWE-REQ-003,032 | UART Command Handler, Position Monitoring Unit | uart_command_handler.[ch], position_monitoring_unit.[ch] | UTC-1-03, UTC-4-03 | SYS-TC-004 |
| SYS-REQ-014 | SWE-REQ-014 | LED Indication | led_indication.[ch] | UTC-5-01 | SYS-TC-009 |
| SYS-REQ-015 | SWE-REQ-015 | LED Indication | led_indication.[ch] | UTC-5-02 | SYS-TC-002, SYS-TC-010, SYS-TC-011 |
| SYS-REQ-016 | SWE-REQ-016 | LED Indication | led_indication.[ch] | UTC-5-03 | SYS-TC-010, SYS-TC-011 |
| SYS-REQ-017 | SWE-REQ-014,021 | System Initialization, LED Indication | system_initialization.[ch], led_indication.[ch] | UTC-5-01, UTC-6-01 | SYS-TC-001 |
| SYS-REQ-018 | SWE-REQ-021 | System Initialization | system_initialization.[ch] | UTC-6-01 | SYS-TC-001 |
| SYS-REQ-019 | SWE-REQ-011,022 | Position Monitoring Unit, System Initialization | position_monitoring_unit.[ch], system_initialization.[ch] | UTC-4-01, UTC-6-01 | SYS-TC-001, SYS-TC-002 |
| SYS-REQ-020 | SWE-REQ-023 | Flap Actuator Controller | flap_actuator_controller.[ch] | UTC-2-05 | SYS-TC-011 |
| SYS-REQ-021 | SWE-REQ-026 | Flap Actuator Controller | flap_actuator_controller.[ch] | UTC-2-04 | SYS-TC-004 |
| SYS-REQ-022 | SWE-REQ-017 | UART Command Handler | uart_command_handler.[ch] | UTC-1-04 | SYS-TC-003 |
| SYS-REQ-023 | SWE-REQ-018 | Position Monitoring Unit | position_monitoring_unit.[ch] | NOT TRACED | NOT TRACED |
| SYS-REQ-024 | SWE-REQ-019 | Motor Control Unit | motor_control_unit.[ch] | UTC-3-01 | NOT TRACED |
| SYS-REQ-025 | SWE-REQ-020 | LED Indication | led_indication.[ch] | NOT TRACED | NOT TRACED |
| SYS-REQ-026 | SWE-REQ-034 | Flap Actuator Controller | flap_actuator_controller.[ch] | NOT TRACED | NOT TRACED |
| SYS-REQ-027 | SWE-REQ-034 | Flap Actuator Controller | flap_actuator_controller.[ch] | NOT TRACED | NOT TRACED |
| SYS-REQ-028 | SWE-REQ-034 | Flap Actuator Controller | flap_actuator_controller.[ch] | NOT TRACED | NOT TRACED |
| SYS-REQ-029 | SWE-REQ-004 | Flap Actuator Controller | flap_actuator_controller.[ch] | UTC-2-01 | SYS-TC-006 |
| SYS-REQ-030 | SWE-REQ-035 | Flap Actuator Controller | flap_actuator_controller.[ch] | NOT TRACED | NOT TRACED |
| SYS-REQ-031 | SWE-REQ-027,032 | Position Monitoring Unit | position_monitoring_unit.[ch] | UTC-4-03 | SYS-TC-005 |
| SYS-REQ-032 | SWE-REQ-033 | UART Command Handler | uart_command_handler.[ch] | UTC-1-05 | NOT TRACED |
| SYS-REQ-033 | SWE-REQ-037 | Flap Actuator Controller | flap_actuator_controller.[ch] | NOT TRACED | NOT TRACED |
| SYS-REQ-034 | SWE-REQ-029 | Flap Actuator Controller | flap_actuator_controller.[ch] | UTC-2-03 | NOT TRACED |
| SYS-REQ-035 | SWE-REQ-039 | LED Indication | led_indication.[ch] | UTC-5-03 | SYS-TC-011 |

# Backward Trace Matrix
| ST | UT | Code | Unit | SWE | SYS |
|----|----|------|------|-----|-----|
| SYS-TC-001 | UTC-5-01, UTC-6-01 | led_indication.[ch], system_initialization.[ch] | LED Indication, System Initialization | SWE-REQ-014,021 | SYS-REQ-017,018,019 |
| SYS-TC-002 | NOT TRACED | led_indication.[ch] | LED Indication | SWE-REQ-015 | SYS-REQ-019,015 |
| SYS-TC-003 | UTC-1-01, UTC-2-02 | uart_command_handler.[ch], flap_actuator_controller.[ch] | UART Command Handler, Flap Actuator Controller | SWE-REQ-001,005,017,024 | SYS-REQ-001,002,022 |
| SYS-TC-004 | UTC-1-02, UTC-4-03 | uart_command_handler.[ch], position_monitoring_unit.[ch] | UART Command Handler, Position Monitoring Unit | SWE-REQ-002,003,031,032 | SYS-REQ-004,013,021 |
| SYS-TC-005 | UTC-4-03 | position_monitoring_unit.[ch] | Position Monitoring Unit | SWE-REQ-013,032 | SYS-REQ-011,031 |
| SYS-TC-006 | UTC-2-01 | flap_actuator_controller.[ch] | Flap Actuator Controller | SWE-REQ-004 | SYS-REQ-029 |
| SYS-TC-007 | UTC-4-01 | position_monitoring_unit.[ch] | Position Monitoring Unit | SWE-REQ-011 | SYS-REQ-008,009,010 |
| SYS-TC-008 | UTC-3-01, UTC-3-02 | motor_control_unit.[ch] | Motor Control Unit | SWE-REQ-005,008,009,010 | SYS-REQ-005,006,007 |
| SYS-TC-009 | UTC-5-01 | led_indication.[ch] | LED Indication | SWE-REQ-014 | SYS-REQ-014 |
| SYS-TC-010 | UTC-5-02, UTC-5-03 | led_indication.[ch] | LED Indication | SWE-REQ-015,016 | SYS-REQ-015,016 |
| SYS-TC-011 | UTC-2-05, UTC-4-01, UTC-5-03 | flap_actuator_controller.[ch], position_monitoring_unit.[ch], led_indication.[ch] | Flap Actuator Controller, Position Monitoring Unit, LED Indication | SWE-REQ-001,006,009,010,015,016,020,035,039 | SYS-REQ-001,002,003,009,010,015,016,020,035 |

# Coverage Gaps
## SYS without ST
| SYS-REQ ID | Not Traced ST |
|------------|---------------|
| SYS-REQ-012 | NOT TRACED |
| SYS-REQ-023 | NOT TRACED |
| SYS-REQ-024 | NOT TRACED |
| SYS-REQ-025 | NOT TRACED |
| SYS-REQ-026 | NOT TRACED |
| SYS-REQ-027 | NOT TRACED |
| SYS-REQ-028 | NOT TRACED |
| SYS-REQ-030 | NOT TRACED |
| SYS-REQ-032 | NOT TRACED |
| SYS-REQ-033 | NOT TRACED |
| SYS-REQ-034 | NOT TRACED |

## SWE without UT
| SWE-REQ ID | Not Traced UT |
|------------|---------------|
| SWE-REQ-012 | NOT TRACED |
| SWE-REQ-018 | NOT TRACED |
| SWE-REQ-022 | NOT TRACED |
| SWE-REQ-028 | NOT TRACED |
| SWE-REQ-030 | NOT TRACED |
| SWE-REQ-034 | NOT TRACED |
| SWE-REQ-035 | NOT TRACED |
| SWE-REQ-036 | NOT TRACED |
| SWE-REQ-037 | NOT TRACED |
| SWE-REQ-038 | NOT TRACED |
| SWE-REQ-040 | NOT TRACED |

## SWE without Code
| SWE-REQ ID | Not Traced Code |
|------------|-----------------|
| SWE-REQ-012 | NOT TRACED |
| SWE-REQ-018 | NOT TRACED |
| SWE-REQ-028 | NOT TRACED |
| SWE-REQ-030 | NOT TRACED |
| SWE-REQ-034 | NOT TRACED |
| SWE-REQ-036 | NOT TRACED |
| SWE-REQ-037 | NOT TRACED |
| SWE-REQ-038 | NOT TRACED |
| SWE-REQ-040 | NOT TRACED |

## Orphan Tests
| Test ID | Not Traced To Any Requirement |
|---------|------------------------------|
| NONE | NONE |

## Orphan Code Files
| Code File | Not Traced to Requirement |
|-----------|--------------------------|
| code/src/main.c | NOT TRACED |

# END OF TRACEABILITY REPORT
