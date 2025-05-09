#include <glib.h>
#include <glib-object.h>
#include <blockdev/utils.h>

#ifndef BD_SMART
#define BD_SMART

GQuark bd_smart_error_quark (void);
#define BD_SMART_ERROR bd_smart_error_quark ()

/**
 * BDSmartError:
 * @BD_SMART_ERROR_TECH_UNAVAIL: SMART support not available.
 * @BD_SMART_ERROR_FAILED: General error.
 * @BD_SMART_ERROR_INVALID_ARGUMENT: Invalid argument.
 */
typedef enum {
    BD_SMART_ERROR_TECH_UNAVAIL,
    BD_SMART_ERROR_FAILED,
    BD_SMART_ERROR_INVALID_ARGUMENT,
} BDSmartError;

typedef enum {
    BD_SMART_TECH_ATA = 0,
    BD_SMART_TECH_SCSI = 1,
} BDSmartTech;

typedef enum {
    BD_SMART_TECH_MODE_INFO         = 1 << 0,
    BD_SMART_TECH_MODE_SELFTEST     = 1 << 1,
} BDSmartTechMode;

/**
 * BDSmartATAOfflineDataCollectionStatus:
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_NEVER_STARTED: Offline data collection activity was never started.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_NO_ERROR: Offline data collection activity was completed without error. Indicates a passed test.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_IN_PROGRESS: Offline data collection activity is in progress.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_SUSPENDED_INTR: Offline data collection activity was suspended by an interrupting command from host.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_ABORTED_INTR: Offline data collection activity was aborted by an interrupting command from host.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_ABORTED_ERROR: Offline data collection activity was aborted by the device with a fatal error. Indicates a failed test.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_VENDOR_SPECIFIC: Offline data collection activity is in a Vendor Specific state.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_RESERVED: Offline data collection activity is in a Reserved state.
 */
typedef enum {
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_NEVER_STARTED   = 0x00,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_NO_ERROR        = 0x02,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_IN_PROGRESS     = 0x03,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_SUSPENDED_INTR  = 0x04,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_ABORTED_INTR    = 0x05,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_ABORTED_ERROR   = 0x06,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_VENDOR_SPECIFIC = 0x40,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_STATUS_RESERVED        = 0x3F,
} BDSmartATAOfflineDataCollectionStatus;

/**
 * BDSmartATAOfflineDataCollectionCapabilities:
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_NOT_SUPPORTED: Offline data collection not supported.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_EXEC_OFFLINE_IMMEDIATE: Execute Offline Immediate function supported.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_OFFLINE_ABORT: Abort Offline collection upon new command.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_OFFLINE_SURFACE_SCAN: Offline surface scan supported.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_SELF_TEST: Self-test supported.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_CONVEYANCE_SELF_TEST: Conveyance Self-test supported.
 * @BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_SELECTIVE_SELF_TEST: Selective Self-test supported.
 */
typedef enum {
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_NOT_SUPPORTED          = 0x00,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_EXEC_OFFLINE_IMMEDIATE = 0x01,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_OFFLINE_ABORT          = 0x04,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_OFFLINE_SURFACE_SCAN   = 0x08,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_SELF_TEST              = 0x10,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_CONVEYANCE_SELF_TEST   = 0x20,
    BD_SMART_ATA_OFFLINE_DATA_COLLECTION_CAP_SELECTIVE_SELF_TEST    = 0x40,
} BDSmartATAOfflineDataCollectionCapabilities;

/**
 * BDSmartATASelfTestStatus:
 * @BD_SMART_ATA_SELF_TEST_STATUS_COMPLETED_NO_ERROR: The previous self-test routine completed without error or no self-test has ever been run.
 * @BD_SMART_ATA_SELF_TEST_STATUS_ABORTED_HOST: The self-test routine was aborted by the host.
 * @BD_SMART_ATA_SELF_TEST_STATUS_INTR_HOST_RESET: The self-test routine was interrupted by the host with a hard or soft reset.
 * @BD_SMART_ATA_SELF_TEST_STATUS_ERROR_FATAL: A fatal error or unknown test error occurred while the device was executing its self-test routine and the device was unable to complete the self-test routine.
 * @BD_SMART_ATA_SELF_TEST_STATUS_ERROR_UNKNOWN: The previous self-test completed having a test element that failed and the test element that failed is not known.
 * @BD_SMART_ATA_SELF_TEST_STATUS_ERROR_ELECTRICAL: The previous self-test completed having the electrical element of the test failed.
 * @BD_SMART_ATA_SELF_TEST_STATUS_ERROR_SERVO: The previous self-test completed having the servo (and/or seek) element of the test failed.
 * @BD_SMART_ATA_SELF_TEST_STATUS_ERROR_READ: The previous self-test completed having the read element of the test failed.
 * @BD_SMART_ATA_SELF_TEST_STATUS_ERROR_HANDLING: The previous self-test completed having a test element that failed and the device is suspected of having handling damage.
 * @BD_SMART_ATA_SELF_TEST_STATUS_IN_PROGRESS: Self-test routine in progress.
 */
typedef enum {
    BD_SMART_ATA_SELF_TEST_STATUS_COMPLETED_NO_ERROR = 0x00,
    BD_SMART_ATA_SELF_TEST_STATUS_ABORTED_HOST       = 0x01,
    BD_SMART_ATA_SELF_TEST_STATUS_INTR_HOST_RESET    = 0x02,
    BD_SMART_ATA_SELF_TEST_STATUS_ERROR_FATAL        = 0x03,
    BD_SMART_ATA_SELF_TEST_STATUS_ERROR_UNKNOWN      = 0x04,
    BD_SMART_ATA_SELF_TEST_STATUS_ERROR_ELECTRICAL   = 0x05,
    BD_SMART_ATA_SELF_TEST_STATUS_ERROR_SERVO        = 0x06,
    BD_SMART_ATA_SELF_TEST_STATUS_ERROR_READ         = 0x07,
    BD_SMART_ATA_SELF_TEST_STATUS_ERROR_HANDLING     = 0x08,
    BD_SMART_ATA_SELF_TEST_STATUS_IN_PROGRESS        = 0x0F,
} BDSmartATASelfTestStatus;

/**
 * BDSmartATACapabilities:
 * @BD_SMART_ATA_CAP_ATTRIBUTE_AUTOSAVE: Saves SMART data before entering power-saving mode.
 * @BD_SMART_ATA_CAP_AUTOSAVE_TIMER: Supports SMART auto save timer.
 * @BD_SMART_ATA_CAP_ERROR_LOGGING: Error logging supported.
 * @BD_SMART_ATA_CAP_GP_LOGGING: General Purpose Logging supported.
 */
typedef enum {
    BD_SMART_ATA_CAP_ATTRIBUTE_AUTOSAVE = 1 << 0,
    BD_SMART_ATA_CAP_AUTOSAVE_TIMER     = 1 << 1,
    BD_SMART_ATA_CAP_ERROR_LOGGING      = 1 << 2,
    BD_SMART_ATA_CAP_GP_LOGGING         = 1 << 3,
} BDSmartATACapabilities;

/**
 * BDSmartATAAttributeUnit:
 * @BD_SMART_ATA_ATTRIBUTE_UNIT_UNKNOWN: Unknown.
 * @BD_SMART_ATA_ATTRIBUTE_UNIT_NONE: Dimensionless value.
 * @BD_SMART_ATA_ATTRIBUTE_UNIT_MSECONDS: Milliseconds.
 * @BD_SMART_ATA_ATTRIBUTE_UNIT_SECTORS: Sectors.
 * @BD_SMART_ATA_ATTRIBUTE_UNIT_MKELVIN: Millikelvin.
 * @BD_SMART_ATA_ATTRIBUTE_UNIT_SMALL_PERCENT: Percentage with 3 decimal points.
 * @BD_SMART_ATA_ATTRIBUTE_UNIT_PERCENT: Integer percentage.
 * @BD_SMART_ATA_ATTRIBUTE_UNIT_MB: Megabytes.
 */
typedef enum {
    BD_SMART_ATA_ATTRIBUTE_UNIT_UNKNOWN,
    BD_SMART_ATA_ATTRIBUTE_UNIT_NONE,
    BD_SMART_ATA_ATTRIBUTE_UNIT_MSECONDS,
    BD_SMART_ATA_ATTRIBUTE_UNIT_SECTORS,
    BD_SMART_ATA_ATTRIBUTE_UNIT_MKELVIN,
    BD_SMART_ATA_ATTRIBUTE_UNIT_SMALL_PERCENT,
    BD_SMART_ATA_ATTRIBUTE_UNIT_PERCENT,
    BD_SMART_ATA_ATTRIBUTE_UNIT_MB,
} BDSmartATAAttributeUnit;

/**
 * BDSmartATAAttributeFlag:
 * @BD_SMART_ATA_ATTRIBUTE_FLAG_PREFAILURE: Pre-failure/advisory bit: If the value of this bit equals zero, an attribute value less than or equal to its corresponding attribute threshold indicates an advisory condition where the usage or age of the device has exceeded its intended design life period. If the value of this bit equals one, an attribute value less than or equal to its corresponding attribute threshold indicates a prefailure condition where imminent loss of data is being predicted.
 * @BD_SMART_ATA_ATTRIBUTE_FLAG_ONLINE: On-line data collection bit: If the value of this bit equals zero, then the attribute value is updated only during off-line data collection activities. If the value of this bit equals one, then the attribute value is updated during normal operation of the device or during both normal operation and off-line testing.
 * @BD_SMART_ATA_ATTRIBUTE_FLAG_PERFORMANCE: Performance type bit (vendor specific).
 * @BD_SMART_ATA_ATTRIBUTE_FLAG_ERROR_RATE: Errorrate type bit (vendor specific).
 * @BD_SMART_ATA_ATTRIBUTE_FLAG_EVENT_COUNT: Eventcount bit (vendor specific).
 * @BD_SMART_ATA_ATTRIBUTE_FLAG_SELF_PRESERVING: Selfpereserving bit (vendor specific).
 * @BD_SMART_ATA_ATTRIBUTE_FLAG_OTHER: Reserved.
 */
typedef enum {
    BD_SMART_ATA_ATTRIBUTE_FLAG_PREFAILURE      = 0x0001,
    BD_SMART_ATA_ATTRIBUTE_FLAG_ONLINE          = 0x0002,
    BD_SMART_ATA_ATTRIBUTE_FLAG_PERFORMANCE     = 0x0004,
    BD_SMART_ATA_ATTRIBUTE_FLAG_ERROR_RATE      = 0x0008,
    BD_SMART_ATA_ATTRIBUTE_FLAG_EVENT_COUNT     = 0x0010,
    BD_SMART_ATA_ATTRIBUTE_FLAG_SELF_PRESERVING = 0x0020,
    BD_SMART_ATA_ATTRIBUTE_FLAG_OTHER           = 0xffc0,
} BDSmartATAAttributeFlag;

/**
 * BDSmartATAAttribute:
 * @id: Attribute Identifier.
 * @name: A free-form representation of the attribute name, implementation-dependent (e.g. libatasmart internal strings or smartmontools' drivedb.h names).
 * @well_known_name: Translated well-known attribute name (in libatasmart style, e.g. 'raw-read-error-rate') or %NULL in case of unknown, untrusted or vendor-specific value.
 * @value: The normalized value or -1 if unknown.
 * @worst: The worst normalized value of -1 if unknown.
 * @threshold: The threshold of a normalized value or -1 if unknown.
 * @failed_past: Indicates a failure that happened in the past (the normalized worst value is below the threshold).
 * @failing_now: Indicates a failure that is happening now (the normalized value is below the threshold).
 * @value_raw: The raw value of the attribute.
 * @flags: Bitmask of attribute flags. See #BDSmartATAAttributeFlag.
 * @pretty_value: Numerical representation of the parsed raw value, presented in @pretty_value_unit units.
 * @pretty_value_unit: The unit of the parsed raw value.
 * @pretty_value_string: A free-form string representation of the raw value intended for user presentation or %NULL.
 */
typedef struct BDSmartATAAttribute {
    guint8 id;
    gchar *name;
    gchar *well_known_name;
    gint value;
    gint worst;
    gint threshold;
    gboolean failed_past;
    gboolean failing_now;
    guint16 flags;
    guint64 value_raw;
    gint64 pretty_value;
    BDSmartATAAttributeUnit pretty_value_unit;
    gchar *pretty_value_string;
} BDSmartATAAttribute;

/**
 * BDSmartATA:
 * @smart_supported: Indicates that the device has SMART capability.
 * @smart_enabled: Indicates that the SMART support is enabled.
 * @overall_status_passed: %TRUE if the device SMART overall-health self-assessment test result has passed.
 * @offline_data_collection_status: The offline data collection status. See #BDSmartATAOfflineDataCollectionStatus.
 * @auto_offline_data_collection_enabled: %TRUE if Automatic Offline Data Collection is enabled. Only supported with the smartmontools plugin.
 * @offline_data_collection_completion: Total time in seconds to complete Offline data collection.
 * @offline_data_collection_capabilities: Bitmask of offline data collection capabilities, see #BDSmartATAOfflineDataCollectionCapabilities. Only supported with the smartmontools plugin.
 * @self_test_status: Self-test execution status. See #BDSmartATASelfTestStatus.
 * @self_test_percent_remaining: The percentage remaining of a running self-test.
 * @self_test_polling_short: Short self-test routine recommended polling time in minutes or 0 if not supported.
 * @self_test_polling_extended: Extended self-test routine recommended polling time in minutes or 0 if not supported.
 * @self_test_polling_conveyance: Conveyance self-test routine recommended polling time in minutes or 0 if not supported.
 * @smart_capabilities: Bitmask of device misc. SMART capabilities. See #BDSmartATACapabilities. Only supported with the smartmontools plugin.
 * @attributes: (array zero-terminated=1): A list of reported SMART attributes.
 * @power_on_time: The count of minutes in power-on state.
 * @power_cycle_count: The count of full hard disk power on/off cycles.
 * @temperature: The current drive temperature in Kelvin or 0 when temperature is not reported.
 */
typedef struct BDSmartATA {
    gboolean smart_supported;
    gboolean smart_enabled;
    gboolean overall_status_passed;
    BDSmartATAOfflineDataCollectionStatus offline_data_collection_status;
    gboolean auto_offline_data_collection_enabled;
    gint offline_data_collection_completion;
    guint offline_data_collection_capabilities;
    BDSmartATASelfTestStatus self_test_status;
    gint self_test_percent_remaining;
    gint self_test_polling_short;
    gint self_test_polling_extended;
    gint self_test_polling_conveyance;
    guint smart_capabilities;
    guint power_on_time;
    guint temperature;
    BDSmartATAAttribute **attributes;
    guint64 power_cycle_count;
} BDSmartATA;


/* TODO: check against some other SCSI implementation for the right wording */
/**
 * BDSmartSCSIInformationalException:
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_NONE: No SCSI Informational Exception raised.
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_ABORTED_COMMAND: Warning - aborted command [asc 0x0b, ascq 0x00].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_TEMPERATURE_EXCEEDED: Warning - specified temperature exceeded [asc 0x0b, ascq 0x01].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_ENCLOSURE_DEGRADED: Warning - enclosure degraded [asc 0x0b, ascq 0x02].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_BACKGROUND_SELFTEST_FAILED: Warning - background self-test failed [asc 0x0b, ascq 0x03].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_BACKGROUND_PRESCAN_MEDIUM_ERROR: Warning - background pre-scan detected medium error [asc 0x0b, ascq 0x04].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_BACKGROUND_SCAN_MEDIUM_ERROR: Warning - background medium scan detected medium error [asc 0x0b, ascq 0x05].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_NV_CACHE_VOLATILE: Warning - non-volatile cache now volatile [asc 0x0b, ascq 0x06].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_NV_CACHE_DEGRADED_POWER: Warning - degraded power to non-volatile cache  [asc 0x0b, ascq 0x07].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_POWER_LOSS_EXPECTED: Warning - power loss expected [asc 0x0b, ascq 0x08].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_STATISTICS_NOTIFICATION: Warning - device statistics notification active [asc 0x0b, ascq 0x09].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_HIGH_CRITICAL_TEMP: Warning - high critical temperature limit exceeded [asc 0x0b, ascq 0x0a].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_LOW_CRITICAL_TEMP: Warning - low critical temperature limit exceeded [asc 0x0b, ascq 0x0b].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_HIGH_OPERATING_TEMP: Warning - high operating temperature limit exceeded [asc 0x0b, ascq 0x0c].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_LOW_OPERATING_TEMP: Warning - low operating temperature limit exceeded [asc 0x0b, ascq 0x0d].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_HIGH_CRITICAL_HUMIDITY: Warning - high critical humidity limit exceeded [asc 0x0b, ascq 0x0e].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_LOW_CRITICAL_HUMIDITY: Warning - low critical humidity limit exceeded [asc 0x0b, ascq 0x0f].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_HIGH_OPERATING_HUMIDITY: Warning - high operating humidity limit exceeded [asc 0x0b, ascq 0x10].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_LOW_OPERATING_HUMIDITY: Warning - low operating humidity limit exceeded [asc 0x0b, ascq 0x11].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_MICROCODE_SECURITY_RISK: Warning - microcode security at risk [asc 0x0b, ascq 0x12].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_MICROCODE_SIGNATURE_VALIDATION_FAILURE: Warning - microcode digital signature validation failure [asc 0x0b, ascq 0x13].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_PHYSICAL_ELEMENT_STATUS_CHANGE: Warning - physical element status change [asc 0x0b, ascq 0x14].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_FAILURE_PREDICTION_THRESH: Failure prediction threshold exceeded [asc 0x5d, ascq 0x00, ascq 0xff].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_MEDIA_FAILURE_PREDICTION_THRESH: Media failure prediction threshold exceeded [asc 0x5d, ascq 0x01].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_LOGICAL_UNIT_FAILURE_PREDICTION_THRESH: Logical unit failure prediction threshold exceeded [asc 0x5d, ascq 0x02].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_SPARE_EXHAUSTION_PREDICTION_THRESH: Spare area exhaustion prediction threshold exceeded [asc 0x5d, ascq 0x03].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_HARDWARE_IMPENDING_FAILURE: Hardware impending failure [asc 0x5d, ascq 0x10..0x1d].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_CONTROLLER_IMPENDING_FAILURE: Controller impending failure [asc 0x5d, ascq 0x20..0x2c].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_DATA_CHANNEL_IMPENDING_FAILURE: Data channel impending failure [asc 0x5d, ascq 0x30..0x3c].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_SERVO_IMPENDING_FAILURE: Servo impending failure [asc 0x5d, ascq 0x40..0x4c].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_SPINDLE_IMPENDING_FAILURE: Spindle impending failure [asc 0x5d, ascq 0x50..0x5c].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_FIRMWARE_IMPENDING_FAILURE: Firmware impending failure [asc 0x5d, ascq 0x60..0x6c].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_MEDIA_ENDURANCE_LIMIT: Media impending failure endurance limit met [asc 0x5d, ascq 0x73].
 * @BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_UNSPECIFIED: Unspecified warning.
 */
typedef enum {
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_NONE,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_ABORTED_COMMAND,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_TEMPERATURE_EXCEEDED,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_ENCLOSURE_DEGRADED,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_BACKGROUND_SELFTEST_FAILED,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_BACKGROUND_PRESCAN_MEDIUM_ERROR,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_BACKGROUND_SCAN_MEDIUM_ERROR,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_NV_CACHE_VOLATILE,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_NV_CACHE_DEGRADED_POWER,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_POWER_LOSS_EXPECTED,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_STATISTICS_NOTIFICATION,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_HIGH_CRITICAL_TEMP,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_LOW_CRITICAL_TEMP,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_HIGH_OPERATING_TEMP,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_LOW_OPERATING_TEMP,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_HIGH_CRITICAL_HUMIDITY,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_LOW_CRITICAL_HUMIDITY,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_HIGH_OPERATING_HUMIDITY,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_LOW_OPERATING_HUMIDITY,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_MICROCODE_SECURITY_RISK,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_MICROCODE_SIGNATURE_VALIDATION_FAILURE,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_PHYSICAL_ELEMENT_STATUS_CHANGE,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_FAILURE_PREDICTION_THRESH,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_MEDIA_FAILURE_PREDICTION_THRESH,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_LOGICAL_UNIT_FAILURE_PREDICTION_THRESH,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_SPARE_EXHAUSTION_PREDICTION_THRESH,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_HARDWARE_IMPENDING_FAILURE,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_CONTROLLER_IMPENDING_FAILURE,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_DATA_CHANNEL_IMPENDING_FAILURE,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_SERVO_IMPENDING_FAILURE,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_SPINDLE_IMPENDING_FAILURE,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_FIRMWARE_IMPENDING_FAILURE,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_MEDIA_ENDURANCE_LIMIT,
    BD_SMART_SCSI_INFORMATIONAL_EXCEPTION_UNSPECIFIED,
} BDSmartSCSIInformationalException;

/**
 * BDSmartSCSIBackgroundScanStatus:
 * @BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_NO_SCANS_ACTIVE: No scans active.
 * @BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_SCAN_ACTIVE: Scan is active.
 * @BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_PRESCAN_ACTIVE: Pre-scan is active.
 * @BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_HALTED_ERROR_FATAL: Halted due to fatal error.
 * @BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_HALTED_PATTERN_VENDOR_SPECIFIC: Halted due to a vendor specific pattern of error.
 * @BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_HALTED_ERROR_PLIST: Halted due to medium formatted without P-List.
 * @BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_HALTED_VENDOR_SPECIFIC: Halted - vendor specific cause.
 * @BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_HALTED_TEMPERATURE: Halted due to temperature out of range.
 * @BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_BMS_TIMER: Waiting until BMS interval timer expires.
 */
typedef enum {
    BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_NO_SCANS_ACTIVE                = 0x00,
    BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_SCAN_ACTIVE                    = 0x01,
    BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_PRESCAN_ACTIVE                 = 0x02,
    BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_HALTED_ERROR_FATAL             = 0x03,
    BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_HALTED_PATTERN_VENDOR_SPECIFIC = 0x04,
    BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_HALTED_ERROR_PLIST             = 0x05,
    BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_HALTED_VENDOR_SPECIFIC         = 0x06,
    BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_HALTED_TEMPERATURE             = 0x07,
    BD_SMART_SCSI_BACKGROUND_SCAN_STATUS_BMS_TIMER                      = 0x08,
} BDSmartSCSIBackgroundScanStatus;

/**
 * BDSmartSCSI:
 * @smart_supported: Indicates that the device has SMART capability.
 * @smart_enabled: Indicates that the SMART support is enabled.
 * @overall_status_passed: %TRUE if the device SMART overall-health self-assessment test result has passed, %FALSE otherwise with @scsi_ie fields set.
 * @scsi_ie: The reported SCSI Informational Exception in a simplified form. See #BDSmartSCSIInformationalException.
 * @scsi_ie_asc: The reported SCSI Informational Exception ASC (Additional Sense Code) value (only values of 0xb - warnings and 0x5d - impending failures are taken in account).
 * @scsi_ie_ascq: The reported SCSI Informational Exception ASCQ (Additional Sense Code Qualifier) value.
 * @scsi_ie_string: String representation of the current SCSI Informational Exception.
 * @background_scan_status: Background scan status, see #BDSmartSCSIBackgroundScanStatus.
 * @background_scan_progress: Percent of a background scan progress.
 * @background_scan_runs: Number of background scans performed.
 * @background_medium_scan_runs: Number of background medium scans performed.
 * @read_errors_corrected_eccfast: Error counter log - read errors corrected by ECC fast.
 * @read_errors_corrected_eccdelayed: Error counter log - read errors corrected by ECC delayed.
 * @read_errors_corrected_rereads: Error counter log - read errors corrected by rereads.
 * @read_errors_corrected_total: Error counter log - total read errors corrected.
 * @read_errors_uncorrected: Error counter log - total uncorrected read errors.
 * @read_processed_bytes: Error counter log - total bytes processed.
 * @write_errors_corrected_eccfast: Error counter log - write errors corrected by ECC fast.
 * @write_errors_corrected_eccdelayed: Error counter log - write errors corrected by ECC delayed.
 * @write_errors_corrected_rewrites: Error counter log - write errors corrected by rewrites.
 * @write_errors_corrected_total: Error counter log - total write errors corrected.
 * @write_errors_uncorrected: Error counter log - total uncorrected write errors.
 * @write_processed_bytes: Error counter log - total bytes processed.
 * @start_stop_cycle_count: Accumulated start-stop cycles.
 * @start_stop_cycle_lifetime: Specified cycle count over device lifetime.
 * @load_unload_cycle_count: Accumulated load-unload cycles.
 * @load_unload_cycle_lifetime: Specified load-unload count over device lifetime.
 * @scsi_grown_defect_list: Elements in grown defect list.
 * @power_on_time: Accumulated power on time in minutes.
 * @temperature_warning_enabled: Indicates that temperature warning is enabled.
 * @temperature: The current drive temperature in Kelvin or 0 when temperature is not reported.
 * @temperature_drive_trip: The drive trip temperature in Kelvin or 0 when temperature is not reported.
 */
typedef struct BDSmartSCSI {
    gboolean smart_supported;
    gboolean smart_enabled;
    gboolean overall_status_passed;
    BDSmartSCSIInformationalException scsi_ie;
    guint8 scsi_ie_asc;
    guint8 scsi_ie_ascq;
    BDSmartSCSIBackgroundScanStatus background_scan_status;
    gchar *scsi_ie_string;
    gdouble background_scan_progress;
    guint background_scan_runs;
    guint background_medium_scan_runs;
    guint read_errors_corrected_eccfast;
    guint read_errors_corrected_eccdelayed;
    guint read_errors_corrected_rereads;
    guint read_errors_corrected_total;
    guint read_errors_uncorrected;
    guint64 read_processed_bytes;
    guint write_errors_corrected_eccfast;
    guint write_errors_corrected_eccdelayed;
    guint write_errors_corrected_rewrites;
    guint write_errors_corrected_total;
    guint write_errors_uncorrected;
    guint64 write_processed_bytes;
    guint start_stop_cycle_count;
    guint start_stop_cycle_lifetime;
    guint load_unload_cycle_count;
    guint load_unload_cycle_lifetime;
    guint scsi_grown_defect_list;
    guint power_on_time;
    gboolean temperature_warning_enabled;
    guint temperature;
    guint temperature_drive_trip;
} BDSmartSCSI;


/**
 * BDSmartSelfTestOp:
 * @BD_SMART_SELF_TEST_OP_ABORT: Abort a running SMART self-test.
 * @BD_SMART_SELF_TEST_OP_OFFLINE: SMART Immediate Offline Test in background (ATA) or a default self test in foreground (SCSI).
 * @BD_SMART_SELF_TEST_OP_SHORT: SMART Short Self Test in background (ATA) or "Background short" self-test (SCSI).
 * @BD_SMART_SELF_TEST_OP_LONG: SMART Extended Self Test in background (ATA) or "Background long" self-test (SCSI).
 * @BD_SMART_SELF_TEST_OP_CONVEYANCE: SMART Conveyance Self Test in background (ATA only).
 */
typedef enum {
    BD_SMART_SELF_TEST_OP_ABORT,
    BD_SMART_SELF_TEST_OP_OFFLINE,
    BD_SMART_SELF_TEST_OP_SHORT,
    BD_SMART_SELF_TEST_OP_LONG,
    BD_SMART_SELF_TEST_OP_CONVEYANCE,
} BDSmartSelfTestOp;


void bd_smart_ata_free (BDSmartATA *data);
BDSmartATA * bd_smart_ata_copy (BDSmartATA *data);

void bd_smart_ata_attribute_free (BDSmartATAAttribute *attr);
BDSmartATAAttribute * bd_smart_ata_attribute_copy (BDSmartATAAttribute *attr);

void bd_smart_scsi_free (BDSmartSCSI *data);
BDSmartSCSI * bd_smart_scsi_copy (BDSmartSCSI *data);

/*
 * If using the plugin as a standalone library, the following functions should
 * be called to:
 *
 * check_deps() - check plugin's dependencies, returning TRUE if satisfied
 * init()       - initialize the plugin, returning TRUE on success
 * close()      - clean after the plugin at the end or if no longer used
 *
 */
gboolean bd_smart_check_deps (void);
gboolean bd_smart_init (void);
void     bd_smart_close (void);

gboolean bd_smart_is_tech_avail (BDSmartTech tech, guint64 mode, GError **error);


BDSmartATA *   bd_smart_ata_get_info            (const gchar        *device,
                                                 const BDExtraArg  **extra,
                                                 GError            **error);
BDSmartATA *   bd_smart_ata_get_info_from_data  (const guint8       *data,
                                                 gsize               data_len,
                                                 GError            **error);
BDSmartSCSI *  bd_smart_scsi_get_info           (const gchar        *device,
                                                 const BDExtraArg  **extra,
                                                 GError            **error);
gboolean       bd_smart_set_enabled             (const gchar        *device,
                                                 gboolean            enabled,
                                                 const BDExtraArg  **extra,
                                                 GError            **error);
gboolean       bd_smart_device_self_test        (const gchar        *device,
                                                 BDSmartSelfTestOp   operation,
                                                 const BDExtraArg  **extra,
                                                 GError            **error);

#endif  /* BD_SMART */
