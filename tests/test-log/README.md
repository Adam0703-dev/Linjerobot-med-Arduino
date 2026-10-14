
# Test Log

## Purpose

This directory contains records of individual test runs performed during the development and evaluation of the robot's firmware.

Each test run is documented in a separate Markdown file to preserve observations, measurements, failures, and conclusions over time.

## File Naming Convention

Test records follow this naming convention:

`YYYY-MM-DD_TEST-ID.md`

Examples:

- `2026-10-15_SEN-01.md`
- `2026-10-15_MOT-01.md`
- `2026-10-16_NAV-01.md`

If the same test is repeated multiple times on the same day, append a run number:

`YYYY-MM-DD_TEST-ID_RUN-N.md`

Example: `2026-10-15_SEN-01_RUN-02.md`

## Required Information

Each test record should include:

- **Date:** When the test was performed.
- **Test ID:** The identifier of the test case.
- **Firmware revision:** The Git commit hash or revision tested.
- **Test setup:** Hardware configuration and test conditions.
- **Objective:** What the test is intended to verify.
- **Procedure:** The steps followed.
- **Expected result:** The intended behavior.
- **Observed result:** What actually happened.
- **Measurements:** Relevant recorded values.
- **Outcome:** PASS, FAIL, or INCONCLUSIVE.
- **Conclusion:** Interpretation of the result.
- **Follow-up actions:** Changes or further tests required.

## Recording Results

Test results must reflect actual observations. Tests that have not been performed must not be marked as passed.

Failed and inconclusive tests should also be documented, including relevant observations and potential causes.

When firmware changes, record the corresponding Git commit hash so the test results can be traced to the exact code revision.

## Outcome Definitions

- **PASS:** All predefined acceptance criteria were met.
- **FAIL:** One or more acceptance criteria were not met.
- **INCONCLUSIVE:** The test did not provide enough evidence to determine whether the criteria were met.
- **NOT TESTED:** The test has not yet been performed.
