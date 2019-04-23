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
static const char* rtc_co2_k30_spec[] =
  {
    "implementation_id", "RTC_CO2_K30",
    "type_name",         "RTC_CO2_K30",
    "description",       "K30 CO2 Sensor ",
    "version",           "1.0.0",
    "vendor",            "Kenta Tohashi",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
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
RTC_CO2_K30::RTC_CO2_K30(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_CO2Out("CO2", m_CO2)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RTC_CO2_K30::~RTC_CO2_K30()
{
}



RTC::ReturnCode_t RTC_CO2_K30::onInitialize()
{
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

/*
RTC::ReturnCode_t RTC_CO2_K30::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

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
 
  void RTC_CO2_K30Init(RTC::Manager* manager)
  {
    coil::Properties profile(rtc_co2_k30_spec);
    manager->registerFactory(profile,
                             RTC::Create<RTC_CO2_K30>,
                             RTC::Delete<RTC_CO2_K30>);
  }
  
};


