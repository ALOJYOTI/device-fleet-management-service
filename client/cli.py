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
    print (resp.success, resp.message)

def set_status(args):
    stub = get_stub()
    req = device_pb2.SetDeviceStatusRequest(
        device_id=args.id,
        state=device_pb2.DeviceState.Value(args.state)
    )
    resp = stub.SetDeviceStatus(req)
    print(resp.success, resp.message)

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

    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
