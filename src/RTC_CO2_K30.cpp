// -*- C++ -*-
/*!
 * @file  RTC_CO2_K30.cpp
 * @brief K30 CO2 Sensor 
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_CO2_K30.h"

// Module specification
// <rtc-template block="module_spec">
static const char *rtc_co2_k30_spec[] =
        {
                "implementation_id", "RTC_CO2_K30",
                "type_name", "RTC_CO2_K30",
                "description", "K30 CO2 Sensor ",
                "version", "1.0.0",
                "vendor", "Kenta Tohashi",
                "category", "Category",
                "activity_type", "PERIODIC",
                "kind", "DataFlowComponent",
                "max_instance", "1",
                "language", "C++",
                "lang_type", "compile",
                // Configuration variables
                "conf.default.port_name", "/dev/ttyUSB0",

                // Widget
                "conf.__widget__.port_name", "text",
                // Constraints

                "conf.__type__.port_name", "string",

                ""
        };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_CO2_K30::RTC_CO2_K30(RTC::Manager *manager)
// <rtc-template block="initializer">
        : RTC::DataFlowComponentBase(manager),
          m_CO2Out("CO2", m_CO2)

// </rtc-template>
{
}

/*!
 * @brief destructor
 */
RTC_CO2_K30::~RTC_CO2_K30() {
}


RTC::ReturnCode_t RTC_CO2_K30::onInitialize() {
    // Registration: InPort/OutPort/Service
    // <rtc-template block="registration">
    // Set InPort buffers

    // Set OutPort buffer
    addOutPort("CO2", m_CO2Out);

    // Set service provider to Ports

    // Set service consumers to Ports

    // Set CORBA Service Ports

    // </rtc-template>

    // <rtc-template block="bind_config">
    // Bind variables and configuration variable
    bindParameter("port_name", m_port_name, "/dev/ttyUSB0");
    // </rtc-template>

    return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_CO2_K30::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RTC_CO2_K30::onActivated(RTC::UniqueId ec_id) {
    serial_fd = open(m_port_name.c_str(), O_RDWR);
    if(serial_fd < 0){
        cerr << "cannot open serial device" << endl;
        return RTC::RTC_ERROR;
    }
    tcgetattr(serial_fd, &old_tio);
    new_tio.c_cflag += CREAD;               // 受信有効
    new_tio.c_cflag += CLOCAL;              // ローカルライン（モデム制御なし）
    new_tio.c_cflag += CS8;                 // データビット:8bit
    new_tio.c_cflag += 0;                   // ストップビット:1bit
    new_tio.c_cflag += 0;                   // パリティ:None

    cfsetispeed( &new_tio, B9600 );
    cfsetospeed( &new_tio, B9600 );

    cfmakeraw(&new_tio);                    // RAWモード

    tcsetattr( serial_fd, TCSAFLUSH, &new_tio );     // デバイスに設定を行う

    ioctl(serial_fd, TCSETS, &new_tio);            // ポートの設定を有効にする
    return RTC::RTC_OK;
}


RTC::ReturnCode_t RTC_CO2_K30::onDeactivated(RTC::UniqueId ec_id) {
    tcsetattr(serial_fd, TCSAFLUSH, &old_tio);
    close(serial_fd);
    return RTC::RTC_OK;
}


RTC::ReturnCode_t RTC_CO2_K30::onExecute(RTC::UniqueId ec_id) {
    uint8_t poll_co2[] = {0xFE, 0x44, 0x00, 0x08, 0x02, 0x9F, 0x25};

    auto *data = new vector<uint8_t>();

    write(serial_fd, poll_co2, sizeof(uint8_t) * 7);
    for (int i = 0; i < 7; i++) {
        uint8_t buf;
        read(serial_fd, &buf, sizeof(uint8_t));
        data->push_back(buf);
    }
    unsigned short result = (unsigned short)data->at(3) * 256 + (unsigned short)data->at(4);
    m_CO2.data = result;
    m_CO2Out.write();
    delete data;
    return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t RTC_CO2_K30::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

void RTC_CO2_K30Init(RTC::Manager *manager) {
    coil::Properties profile(rtc_co2_k30_spec);
    manager->registerFactory(profile,
                             RTC::Create<RTC_CO2_K30>,
                             RTC::Delete<RTC_CO2_K30>);
}

};


