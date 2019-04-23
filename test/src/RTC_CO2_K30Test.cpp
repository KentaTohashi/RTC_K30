// -*- C++ -*-
/*!
 * @file  RTC_CO2_K30Test.cpp
 * @brief K30 CO2 Sensor 
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_CO2_K30Test.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_co2_k30_spec[] =
  {
    "implementation_id", "RTC_CO2_K30Test",
    "type_name",         "RTC_CO2_K30Test",
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
RTC_CO2_K30Test::RTC_CO2_K30Test(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_CO2Out("CO2", m_CO2)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RTC_CO2_K30Test::~RTC_CO2_K30Test()
{
}



RTC::ReturnCode_t RTC_CO2_K30Test::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("CO2", m_CO2In);
  
  // Set OutPort buffer
  
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
RTC::ReturnCode_t RTC_CO2_K30Test::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30Test::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30Test::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30Test::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30Test::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30Test::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30Test::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30Test::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30Test::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30Test::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_CO2_K30Test::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RTC_CO2_K30TestInit(RTC::Manager* manager)
  {
    coil::Properties profile(rtc_co2_k30_spec);
    manager->registerFactory(profile,
                             RTC::Create<RTC_CO2_K30Test>,
                             RTC::Delete<RTC_CO2_K30Test>);
  }
  
};


