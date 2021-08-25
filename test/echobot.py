#!/usr/bin/env python

import os
import time
import tox
import sys
import datetime

savedata_filename = "savedata.tox"
savedata_tmp_filename = "savedata.tox.tmp"

def log_cb(t, level, file_, line, func, message):
    print(level, file_, line, func, message)

def create_tox():
    print('creating options instance')
    options = tox.Options()
    options.set_log_callback(log_cb)
    try:
        with open(savedata_filename, 'rb') as f:
            savedata = f.read()
        print('set savedata')
        options.set_savedata(tox.SAVEDATA_TYPE_TOX_SAVE, savedata)
    except IOError:
        pass
    print('creating tox instance')
    return tox.Tox(options)

def bootstrap(t):
    nodes = [("85.143.221.42", 33445,
        "DA4E4ED4B697F2E9B000EEFE3A34B554ACD3F45F5C96EAEA2516DD7FF9AF7B43"),
        ("2a04:ac00:1:9f00:5054:ff:fe01:becd", 33445,
        "DA4E4ED4B697F2E9B000EEFE3A34B554ACD3F45F5C96EAEA2516DD7FF9AF7B43"),
        ("78.46.73.141", 33445,
        "02807CF4F8BB8FB390CC3794BDF1E8449E9A8392C5D3F2200019DA9F1E812E46"),
        ("2a01:4f8:120:4091::3", 33445,
        "02807CF4F8BB8FB390CC3794BDF1E8449E9A8392C5D3F2200019DA9F1E812E46"),
        ("tox.initramfs.io", 33445,
        "3F0A45A268367C1BEA652F258C85F4A66DA76BCAA667A49E770BCC4917AB6A25"),
        ("tox2.abilinski.com", 33445,
        "7A6098B590BDC73F9723FC59F82B3F9085A64D1B213AAF8E610FD351930D052D"),
        ("205.185.115.131", 53,
        "3091C6BEB2A993F1C6300C16549FABA67098FF3D62C6D253828B531470B53D68"),
        ("tox.kurnevsky.net", 33445,
        "82EF82BA33445A1F91A7DB27189ECFC0C013E06E3DA71F588ED692BED625EC23"),
("tox.initramfs.io", 33445,
        "3F0A45A268367C1BEA652F258C85F4A66DA76BCAA667A49E770BCC4917AB6A25"),
    ]

    for host, port, key in nodes:
        binkey = bytes.fromhex(key)
        print('bootstrap: {}, {}, {}'.format(host, port, key))
        try:
            t.bootstrap(host, port, binkey)
        except tox.error:
            print('error bootstraping')

def print_tox_id(t):
    print("Tox ID: {}".format(t.self_get_address().hex().upper()));

def friend_request_cb(t, public_key, message):
    print('received friend request: {}, {}'.format(public_key, message))
    t.friend_add_norequest(public_key)
    update_savedata_file(t)

def friend_message_cb(t, friend_number, type_, message):
    print('received friend message: {}, {}, {}'.format(
        friend_number, type_, message))
    message_id = t.friend_send_message(friend_number, type_, message)
    print('Message ID: {}'.format(message_id))
    friends = t.self_get_friend_list()
    for f in friends:
        print(t.friend_get_public_key(f).hex())
        print(t.friend_get_last_online(f))

def self_connection_status_cb(t, connection_status):
    if connection_status == tox.CONNECTION_NONE:
        status = 'offline'
    elif connection_status == tox.CONNECTION_TCP:
        status = 'Online, using TCP'
    elif connection_status == tox.CONNECTION_UDP:
        status = 'Online, using UDP'
    print('changed status: {}'.format(status))

def friend_name_cb(t, friend_number, name):
    print('Friend name: {}, {}'.format(friend_number, name))
    print(t.friend_get_name(friend_number))
    print(t.friend_get_last_online(friend_number))
    update_savedata_file(t)

def friend_status_message_cb(t, friend_number, status_message):
    print('Friend status message: {}, {}'.format(
        friend_number, status_message))
    print(t.friend_get_status_message(friend_number))
    update_savedata_file(t)

def friend_status_cb(t, friend_number, status):
    print('Friend status: {}, {}'.format(friend_number, status))

def friend_connection_status_cb(t, friend_number, connection_status):
    print('Friend connection status: {}, {}'.format(
        friend_number, connection_status))

def friend_typing_cb(t, friend_number, is_typing):
    print('Friend {} is typing: {}'.format(friend_number, is_typing))

def friend_read_receipt_cb(t, friend_number, message_id):
    print('Friend {} received message {}'.format(friend_number, message_id))

def file_recv_cb(t, friend_number, file_number, kind, file_size, filename):
    global fd
    print('Receive request')
    print('frient_number: {}'.format(friend_number))
    print('file_number: {}'.format(file_number))
    print('kind: {}'.format(kind))
    print('file_size: {}'.format(file_size))
    print('filename: {}'.format(filename))
    if kind == 1 and file_size == 0:
        # Null avatar
        t.file_control(friend_number, file_number, tox.FILE_CONTROL_CANCEL)
    elif kind == 0:
        fd = open(filename, 'wb')
        t.file_control(friend_number, file_number, tox.FILE_CONTROL_RESUME)

def file_recv_chunk_cb(t, friend_number, file_number, position, data):
    print('Received chunk from friend {}: file_number={}, position={}'.format(
        friend_number, file_number, position))
    if not data:
        fd.close()
    else:
        fd.write(data)

def update_savedata_file(t):
    print('get_savedata')
    data = t.get_savedata()
    with open(savedata_tmp_filename, 'wb') as f:
        f.write(data)
    os.rename(savedata_tmp_filename, savedata_filename)

if __name__ == '__main__':    
    t = create_tox();

    print('set name')
    t.self_set_name("Echo Bot")
    print(t.self_get_name())
    print(t.self_get_nospam())
    print(t.self_get_public_key())
    print(t.self_get_secret_key())
    print(t.self_get_status_message())
    try: t.self_set_status(-1)
    except ValueError as e: print(e)
    try: t.self_set_status(3)
    except ValueError as e: print(e)
    t.self_set_status(tox.USER_STATUS_BUSY)
    print(t.self_get_status())
    friends = t.self_get_friend_list()
    print(friends)
    print(t.friend_exists(0))
    print(t.friend_exists(1))
    print(t.friend_exists(2))
    for f in friends:
        print(t.friend_get_name(f))
        print(t.friend_get_public_key(f).hex())
        print(t.friend_get_last_online(f))

    print('set status message')
    t.self_set_status_message("Echoing your messages")

    bootstrap(t)
    print_tox_id(t)

    print('set callbacks')
    t.callback_friend_request(friend_request_cb)
    t.callback_friend_message(friend_message_cb)
    t.callback_self_connection_status(self_connection_status_cb)
    t.callback_friend_name(friend_name_cb)
    t.callback_friend_status_message(friend_status_message_cb)
    t.callback_friend_status(friend_status_cb)
    t.callback_friend_connection_status(friend_connection_status_cb)
    t.callback_friend_typing(friend_typing_cb)
    t.callback_friend_read_receipt(friend_read_receipt_cb)
    t.callback_file_recv(file_recv_cb)
    t.callback_file_recv_chunk(file_recv_chunk_cb)

    update_savedata_file(t);
 
    print('Connecting...')

    while 1:
        t.iterate()
        time.sleep(t.iteration_interval()/1000.0)

