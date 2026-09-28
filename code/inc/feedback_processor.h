/**
 * @file feedback_processor.h
 * @brief Feedback Processor – ADC acquisition, validation and position mapping.
 *
 * Software Unit : Feedback Processor
 * Traceability  : SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027,
 *                 SWE-REQ-028, SWE-REQ-030
 *
 * CONFIGURATION GAP: ADC channel, GPIO pin, and the exact ADC-to-position
 * boundary thresholds are assumed defaults.  They MUST be confirmed against
 * hardware characterisation data during integration.
 */
#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>

/* ── ADC boundary configuration (static, SWE-REQ-027/030) ──────────────
 * 12-bit ADC on STM32F407 → range 0 … 4095.
 * Five positions mapped to roughly equal ADC bands.
 * THESE VALUES ARE ASSUMED and must be calibrated per the actual
 * potentiometer + gear arrangement described in env-setup.
 * ──────────────────────────────────────────────────────────────────────── */
#define FB_ADC_MIN              ((uint16_t)0U)
#define FB_ADC_MAX              ((uint16_t)4095U)

#define FB_POS0_LOW             ((uint16_t)0U)
#define FB_POS0_HIGH            ((uint16_t)819U)
#define FB_POS1_LOW             ((uint16_t)820U)
#define FB_POS1_HIGH            ((uint16_t)1638U)
#define FB_POS2_LOW             ((uint16_t)1639U)
#define FB_POS2_HIGH            ((uint16_t)2457U)
#define FB_POS3_LOW             ((uint16_t)2458U)
#define FB_POS3_HIGH            ((uint16_t)3276U)
#define FB_POS4_LOW             ((uint16_t)3277U)
#define FB_POS4_HIGH            ((uint16_t)4095U)

#define FB_POSITION_COUNT       ((uint8_t)5U)

/* Feedback processor states (LLD §3) */
typedef enum
{
    FBPROC_STATE_INIT    = 0U,
    FBPROC_STATE_READY   = 1U,
    FBPROC_STATE_INVALID = 2U
} FbProc_State_t;

/* Position result structure */
typedef struct
{
    uint8_t       position;  /* Mapped logical position (0..4)        */
    uint8_t       valid;     /* 1 = valid reading, 0 = invalid/fault  */
    uint16_t      raw_adc;   /* Raw ADC value (for debug/testability) */
    FbProc_State_t state;
} FbProc_Result_t;

/**
 * @brief Initialise feedback processor (set state to INIT, clear data).
 * Trace: SWE-REQ-020 (via System Init)
 */
void FbProc_Init(void);

/**
 * @brief Acquire a new ADC sample, validate, and map to position.
 * Trace: SWE-REQ-010, SWE-REQ-011, SWE-REQ-017, SWE-REQ-027
 */
void FbProc_Update(void);

/**
 * @brief Get the current mapped position and validity.
 * Trace: SWE-REQ-010, SWE-REQ-027
 *
 * @param[out] p_result  Pointer to feedback result struct.
 */
void FbProc_GetPosition(FbProc_Result_t *p_result);

#endif /* FEEDBACK_PROCESSOR_H */
