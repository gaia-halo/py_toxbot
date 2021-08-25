#!/usr/bin/env python

import tox

print("MODULE METHODS")
print("==============")
print(tox.version_major())
print(tox.version_minor())
print(tox.version_patch())
print(tox.version_is_compatible(0, 2, 10))
print(tox.version_is_compatible(0, 3, 10))
print(tox.public_key_size())
print(tox.secret_key_size())
print(tox.conference_id_size())
print(tox.nospam_size())
print(tox.address_size())
print(tox.max_name_length())
print(tox.max_status_message_length())
print(tox.max_friend_request_length())
print(tox.max_message_length())
print(tox.max_custom_packet_size())
print(tox.hash_length())
print(tox.file_id_length())
print(tox.max_filename_length())
print(tox.max_hostname_length())
print()

o = tox.Options()
print("OPTIONS METHODS")
print("===============")
print(o.get_ipv6_enabled())
print(o.get_udp_enabled())
print(o.get_local_discovery_enabled())
print(o.get_proxy())
print(o.get_start_port())
print(o.get_end_port())
print(o.get_tcp_port())
print(o.get_hole_punching_enabled())

try:
    o.set_proxy(tox.PROXY_TYPE_HTTP)
except ValueError as e:
    print(e)
o.set_proxy(tox.PROXY_TYPE_HTTP, 'localhost')
print(o.get_proxy())
o.set_proxy(tox.PROXY_TYPE_NONE)
print(o.get_proxy())
print(o.get_savedata())
try:
    o.set_savedata(tox.SAVEDATA_TYPE_TOX_SAVE)
except ValueError as e:
    print(e)
o.set_savedata(tox.SAVEDATA_TYPE_TOX_SAVE, b'12345')
print(o.get_savedata())

