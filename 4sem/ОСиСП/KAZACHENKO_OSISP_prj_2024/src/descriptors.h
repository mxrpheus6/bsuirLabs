#define NAME_FILENAME "product"
#define MANUFACTURER_FILENAME "manufacturer"
#define NUMBER_OF_PORTS_FILENAME "maxchild"
#define SERIAL_NUMBER_FILENAME "serial"
#define SPEED_FILENAME "speed"
#define BUS_FILENAME "busnum"
#define DEVICE_NUMBER_FILENAME "devnum"
#define USB_VERSION_FILENAME "version"
#define DEVICE_CLASS_FILENAME "bDeviceClass"
#define DEVICE_SUBCLASS_FILENAME "bDeviceSubClass"
#define DEVICE_PROTOCOL_FILENAME "bDeviceProtocol"
#define MAX_ENDPOINT_SIZE_FILENAME "bMaxPacketSize0"
#define VENDOR_ID_FILENAME "idVendor"
#define PRODUCT_ID_FILENAME "idProduct"
#define DEVICE_REVISION_FILENAME "bcdDevice"
#define NUMBER_OF_CONFIGURATIONS_FILENAME "bNumConfigurations"
#define CONFIG_NUMBER_FILENAME "bConfigurationValue"
#define ATTRIBUTES_FILENAME "bmAttributes"
#define MAX_POWER_FILENAME "bMaxPower"
#define NUMBER_OF_INTERFACES_FILENAME "bNumInterfaces"
#define INTERFACE_NUMBER_FILENAME "bInterfaceNumber"
#define DRIVER_NAME_FILENAME "uevent"
#define ALTERNATE_NUMBER_FILENAME "bAlternateSetting"
#define CLASS_FILENAME "bInterfaceClass"
#define SUBCLASS_FILENAME "bInterfaceSubClass"
#define PROTOCOL_FILENAME "bInterfaceProtocol"
#define NUMBER_OF_ENDPOINTS_FILENAME "bNumEndpoints"

char* read_descriptor(const char *dir, const char *desc);