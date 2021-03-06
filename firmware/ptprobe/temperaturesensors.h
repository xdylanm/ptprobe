#ifndef temperaturesensors_h_
#define temperaturesensors_h_

#include <OneWire.h>

#define MAX_SENSOR_COUNT 4

class TemperatureSensors
{
public:

  static int8_t const ERROR_NDX_OUT_OF_RANGE;
  static int8_t const ERROR_BUS_RESET;
  static int8_t const ERROR_CRC_FAILED;

  struct MAX31850
  {
    MAX31850() : id_(0), probe_T_(0), ref_T_(0), fault_status_(NONE) {}
    uint8_t addr_[8]; // the 64 bit ROM address
    uint8_t id_;      // the 4 bit electrically configured address
    float probe_T_;
    float ref_T_;
    enum Fault {NONE=0, OC=1, GND_SHORT=2, VDD_SHORT=4} fault_status_;
  };

  
  TemperatureSensors(int const bus_pin);

  void begin();

  bool start_conversion(int device_ndx = -1);
  int8_t read_scratchpad(int device_ndx);
  bool conversion_complete(int device_ndx = -1);
  int8_t sensor_count() const { return sensor_count_; }

  MAX31850 const* get_sensor(int device_ndx) const;

  static char const* error_short_label(int8_t fault_code);
  
private:
  static OneWire* bus_;

  MAX31850 device_table_[MAX_SENSOR_COUNT];  // table stores up to 4 
  int8_t sensor_count_;
};


#endif
