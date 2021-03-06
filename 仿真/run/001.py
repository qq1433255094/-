from lib import vrep
import time
import math
import threading

clientID = -1


def Connect(port=20001, ip='127.0.0.1'):
    global clientID
    print('Program started')
    vrep.simxFinish(-1)  # just in case, close all opened connections
    clientID = vrep.simxStart(ip, port, True,
                              True, 5000, 1)  # Connect to V-REP
    if clientID != -1:
        print('Connected to remote API server')
    else:
        print('Failed connecting to remote API server')
        exit()
    return clientID


def GetClientID():
    global clientID
    return clientID


def Start():
    vrep.simxStartSimulation(GetClientID(), vrep.simx_opmode_blocking)


def Stop():
    vrep.simxStopSimulation(GetClientID(), vrep.simx_opmode_blocking)


def GetHandle(name):
    code, Handle = vrep.simxGetObjectHandle(
        GetClientID(), name, vrep.simx_opmode_blocking)
    return Handle


def ReadForceSensor(handle, mode=1):
    if mode == 1:
        code, state, forceVector, torqueVector = vrep.simxReadForceSensor(
            GetClientID(), handle, vrep.simx_opmode_blocking)
    elif mode == 2:
        code, state, forceVector, torqueVector = vrep.simxReadForceSensor(
            GetClientID(), handle, vrep.simx_opmode_streaming)
    elif mode == 3:
        code, state, forceVector, torqueVector = vrep.simxReadForceSensor(
            GetClientID(), handle, vrep.simx_opmode_buffer)

    return forceVector[2]


def ReadFsrGroup(FsrGroup, mode=1):
    data = []
    for i in FsrGroup:
        data.append(ReadForceSensor(i, mode))
    return data


Connect()

target_l = GetHandle("Dummy_target_l")
target_r = GetHandle("Dummy_target_r")
body = GetHandle("NAO")
LFsrFL = GetHandle("NAO_LFsrFL")
LFsrFR = GetHandle("NAO_LFsrFR")
LFsrRL = GetHandle("NAO_LFsrRL")
LFsrRR = GetHandle("NAO_LFsrRR")

RFsrFL = GetHandle("NAO_RFsrFL")
RFsrFR = GetHandle("NAO_RFsrFR")
RFsrRL = GetHandle("NAO_RFsrRL")
RFsrRR = GetHandle("NAO_RFsrRR")

FsrGroup = [LFsrFL, LFsrFR, LFsrRL, LFsrRR,
            RFsrFL, RFsrFR, RFsrRL, RFsrRR]


Position_L = [0.017386972904205322, 0.049652472138404846, -0.3211700916290283]
Position_R = [0.017386972904205322, -0.049652472138404846, -0.3211700916290283]


def SetTargetLPos(position):
    global Position_L, target_l, body
    position_temp = [0, 0, 0]
    for i in range(3):
        position_temp[i] = position[i] + Position_L[i]
    vrep.simxSetObjectPosition(
        GetClientID(), target_l, body, position_temp, vrep.simx_opmode_oneshot)


def SetTargetRPos(position):
    global Position_R, target_r, body
    position_temp = [0, 0, 0]
    for i in range(3):
        position_temp[i] = position[i] + Position_R[i]
    vrep.simxSetObjectPosition(
        GetClientID(), target_r, body, position_temp, vrep.simx_opmode_oneshot)


# def thread_Read_FsrGroup(FsrGroup):
#     ReadForceSensor(FsrGroup, 2)
#     time.sleep(0.05)
#     while True:
#         a = ReadFsrGroup(FsrGroup, 3)
#         print(a)
#         time.sleep(0.05)
# test_thread = threading.Thread(target=thread_Read_FsrGroup, args=(FsrGroup))
# test_thread.setDaemon(True)
# test_thread.start()

Start()

ReadFsrGroup(FsrGroup, 2)
time.sleep(0.05)

Position1 = [0, 0, 0]
Position2 = [0, 0, 0]


a = ReadFsrGroup(FsrGroup, 3)
print(a, sum(a[0:4]), sum(a[4:8]), sum(a))

for i in range(1, 10):
    Position1[1] += 0.003
    SetTargetLPos(Position1)
    Position2[1] += 0.0003
    SetTargetRPos(Position2)
    time.sleep(0.005)

a = ReadFsrGroup(FsrGroup, 3)
print(a, sum(a[0:4]), sum(a[4:8]), sum(a))

step = 0.0002
wight = 0.0003
hight = 0.0005

for i in range(10):

    for i in range(1, 200):
        Position1[1] -= wight
        Position1[0] += step
        Position1[2] = hight*(200-i)*(i)/200.0
        SetTargetLPos(Position1)
        Position2[1] -= wight
        Position2[0] -= step
        SetTargetRPos(Position2)
        time.sleep(0.001)
    time.sleep(0.1)
    for i in range(1, 200):
        Position1[1] += wight
        Position1[0] -= step
        SetTargetLPos(Position1)
        Position2[1] += wight
        Position2[0] += step
        Position2[2] = hight*(200-i)*(i)/200.0
        SetTargetRPos(Position2)
        time.sleep(0.001)
    time.sleep(0.1)

a = ReadFsrGroup(FsrGroup, 3)
print(a, sum(a[0:4]), sum(a[4:8]), sum(a))

time.sleep(2)

Stop()
# for i in range(1, 50):
#     Position[1] += 0.0006

#     vrep.simxSetObjectPosition(
#         clientID, target_l, body, Position, vrep.simx_opmode_blocking)
#     time.sleep(0.005)
