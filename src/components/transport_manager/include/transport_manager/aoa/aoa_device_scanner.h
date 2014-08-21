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

#ifndef SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_AOA_AOA_DEVICE_SCANNER_H_
#define SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_AOA_AOA_DEVICE_SCANNER_H_

#include <map>

#include "transport_manager/transport_adapter/device_scanner.h"
#include "transport_manager/aoa/aoa_device.h"
#include "transport_manager/aoa/aoa_wrapper.h"

namespace transport_manager {
namespace transport_adapter {

class TransportAdapterController;

class AOADeviceScanner : public DeviceScanner {
 public:
  explicit AOADeviceScanner(TransportAdapterController* controller);

 protected:
  virtual TransportAdapter::Error Init();
  virtual TransportAdapter::Error Scan();
  virtual void Terminate();
  virtual bool IsInitialised() const;

 private:
  typedef std::map<AOAWrapper::AOAHandle, AOADevicePtr> DeviceContainer;

  bool initialised_;
  AOAScannerObserver* observer_;
  TransportAdapterController* controller_;
  DeviceContainer devices_;
  sync_primitives::Lock devices_lock_;

  void AddDevice(AOAWrapper::AOAHandle hdl);
  void NotifyDevicesUpdated();

  class ScannerObserver : public AOAScannerObserver {
   public:
    explicit ScannerObserver(AOADeviceScanner* parent);
    void OnConnectedDevice(AOAWrapper::AOAHandle hdl);
   private:
    AOADeviceScanner* parent_;
  };
};

}  // namespace transport_adapter
}  // namespace transport_manager

#endif  // SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_AOA_AOA_DEVICE_SCANNER_H_
