/*
 * Copyright (c) 2014, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "utils/logger.h"

namespace transport_manager {
namespace transport_adapter {

CREATE_LOGGERPTR_GLOBAL(logger_, "TransportManager")

AOAConnectionFactory::AOAConnectionFactory(
    TransportAdapterController* controller)
    : controller_(controller) {
}

TransportAdapter::Error AOAConnectionFactory::Init() {
  return TransportAdapter::OK;
}

bool AOAConnectionFactory::IsInitialised() const {
  return true;
}

TransportAdapter::Error AOAConnectionFactory::CreateConnection(
    const DeviceUID& device_uid, const ApplicationHandle& app_handle) {
  LOG4CXX_TRACE(
      logger_,
      "AOA: create connection DeviceUID: " << &device_uid << ", ApplicationHandle: " << &app_handle);

  DeviceSptr device = controller_->FindDevice(device_uid);
  if (!device) {
    LOG4CXX_ERROR(logger_, "AOA: device " << device_uid << " not found");
    return TransportAdapter::BAD_PARAM;
  }

  AOADevicePtr aoa_device = DeviceSptr::static_pointer_cast<AOADevice>(device);
  ConnectionSptr connection = new AOAConnection(device_uid, app_handle,
                                                controller_,
                                                aoa_device->handle());
  controller_->ConnectionCreated(connection, device_uid, app_handle);

  LOG4CXX_INFO(logger_, "AOA: connection created");
  return TransportAdapter::OK;
}

void AOAConnectionFactory::Terminate() {
}

}  // namespace transport_adapter
}  // namespace transport_manager

