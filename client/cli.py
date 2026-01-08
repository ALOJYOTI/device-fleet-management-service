import argparse
import grpc

import device_pb2_grpc
import device_pb2


def get_stub():
    channel = grpc.insecure_channel("localhost:50051")
    return device_pb2_grpc.DeviceFleetServiceStub(channel)

def register_device(args):
    stub = get_stub()
    req = device_pb2.RegisterDeviceRequest(
        device_id = args.id,
        initial_state = device_pb2.DeviceState.Value(args.state)
    )

    resp = stub.RegisterDevice(req)
    print(f"{'SUCCESS' if resp.success else 'FAILURE'}")
    print(f"{resp.message}")


def set_status(args):
    stub = get_stub()
    req = device_pb2.SetDeviceStatusRequest(
        device_id=args.id,
        state=device_pb2.DeviceState.Value(args.state)
    )
    resp = stub.SetDeviceStatus(req)
    print(f"{'SUCCESS' if resp.success else 'FAILURE'}")
    print(f"{resp.message}")

def get_device_info(args):
    stub = get_stub()
    req = device_pb2.GetDeviceInfoRequest(device_id=args.id)
    resp = stub.GetDeviceInfo(req)
    if resp.found:
        device_state = device_pb2.DeviceState.Name(resp.device.device_state)
        print(f"Device ID: {resp.device.device_id}")
        print(f"State : {device_state}")
    else:
        print("Device not found")

def start_action(args):
    stub = get_stub()

    params = device_pb2.ActionParams(
        target_version=device_pb2.SoftwareVersion.Value(args.version)
    )

    req = device_pb2.InitiateDeviceActionRequest(
        device_id=args.id,
        action_type=args.type,
        params=params
    )

    resp = stub.InitiateDeviceAction(req)

    if resp.success:
        print(f"Action initiated. Action ID: {resp.action_id}")
    else:
        print(f"{resp.message}")

def get_action_status(args):
    stub = get_stub()

    req = device_pb2.GetDeviceActionStatusRequest(action_id=args.action_id)
    resp = stub.GetDeviceActionStatus(req)

    if not resp.found:
        print("Action not found")
        return

    status = device_pb2.ActionStatus.Name(resp.status)
    print(f"Action Status: {status}")

def list_devices(args):
    stub = get_stub()
    resp = stub.ListDevices(device_pb2.ListDevicesRequest())

    for d in resp.devices:
        state = device_pb2.DeviceState.Name(d.device_state)
        print(f"Device ID: {d.device_id}, State: {state}")

def main():
    parser = argparse.ArgumentParser()
    sub = parser.add_subparsers()

    p1 = sub.add_parser("register")
    p1.add_argument("--id", required=True)
    p1.add_argument("--state", required=True,
                    choices=["IDLE", "BUSY", "OFFLINE", "MAINTENANCE"])
    p1.set_defaults(func=register_device)

    p2 = sub.add_parser("set-status")
    p2.add_argument("--id", required=True)
    p2.add_argument("--state", required=True,
                    choices=["IDLE", "BUSY", "OFFLINE", "MAINTENANCE"])
    p2.set_defaults(func=set_status)

    p3 = sub.add_parser("get-device-info")
    p3.add_argument("--id", required=True)
    p3.set_defaults(func=get_device_info)

    p4 = sub.add_parser("start-action")
    p4.add_argument("--id", required=True)
    p4.add_argument("--type", required=True,
                    choices=["SOFTWARE_UPDATE"])
    p4.add_argument("--version", required=True,
                    choices=["V1_0", "V1_1", "V2_0"])
    p4.set_defaults(func=start_action)

    p5 = sub.add_parser("get-action-status")
    p5.add_argument("--action-id", required=True)
    p5.set_defaults(func=get_action_status)

    p6 = sub.add_parser("list-devices")
    p6.set_defaults(func=list_devices)

    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
