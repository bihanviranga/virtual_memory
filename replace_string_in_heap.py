'''
Locate and replace the first occurence of a string
in the heap of a process.

Usage:
	./replace_string_in_heap.py PID search_string replace_string

	- PID : The process ID of the target process.
	- search_string : the ASCII string to be replaced.
	- replace_string : the new ASCII string to replace search_string
'''

import sys

def print_usage_and_exit():
	print("Usage: {} pid search write".format(sys.argv[0]))
	sys.exit(1)

# check usage
if len(sys.argv) != 4:
	print_usage_and_exit()

# get the arguments
pid = int(sys.argv[1])
if pid <= 0:
	print_usage_and_exit()

search_string = str(sys.argv[2])
if search_string == "":
	print_usage_and_exit()

write_string = str(sys.argv[3])
if write_string == "":
	print_usage_and_exit()

# open the maps and mem files of the process
maps_filename = "/proc/{}/maps".format(pid)
print("[*] maps: {}".format(maps_filename))

mem_filename = "/proc/{}/mem".format(pid)
print("[*] mem: {}".format(mem_filename))

# try to access the maps file
try:
	maps_file = open(maps_filename, 'r')
except Exception as e:
	print("[ERROR] Can't open file: {}".format(maps_filename))
	print("\t I/O error({}): {}".format(e.errno, e.strerror))
	sys.exit(1)

# read maps file
for line in maps_file:
	sline = line.split(' ')

	if sline[-1][:-1] != "[heap]":
		continue
	print("[*] Found [heap]")

	# parse the line
	addr = sline[0]
	perm = sline[1]
	offset = sline[2]
	device = sline[3]
	inode = sline[4]
	pathname = sline[-1][:-1]

	print("\tpathname = {}".format(pathname))
	print("\taddresses = {}".format(addr))
	print("\tpermissions = {}".format(perm))
	print("\toffset = {}".format(offset))
	print("\tinode = {}".format(inode))

	# check if there's r/w permission
	if perm[0] != 'r' or perm[1] != 'w':
		print("[*] {} does not have read/write permission.".format(pathname))
		maps_file.close()
		exit(0)

	# get base and limit of the heap in virtual memory
	addr = addr.split("-")
	if len(addr) != 2: # this isn't unlikely unless the OS was drunk
		print("[*] Wrong addr format")
		maps_file.close()
		exit(1)
	addr_start = int(addr[0], 16)
	addr_end = int(addr[1], 16)
	print("\tAddr start: [{:x}] | end: [{:x}]".format(addr_start, addr_end))

	# open and read the memory
	try:
		mem_file = open(mem_filename, 'rb+')	
	except IOError as e:
		print("[ERROR] Can't open file: {}".format(mem_filename))
		print("\tI/O error({}) : {}".format(e.errno, e.strerror))
		map_file.close()
		exit(1)

	# read heap
	mem_file.seek(addr_start)
	heap = mem_file.read(addr_end - addr_start)

	# find string
	try:
		i = heap.index(bytes(search_string, "ASCII"))
	except Exception:
		print("Can't find '{}'".format(search_string))
		maps_file.close()
		mem_file.close()
		exit(0)
	print("[*] Found '{}' at {:x}".format(search_string, i))

	# write the new string
	print("[*] Writing '{}' at {:x}".format(write_string, addr_start + i))
	mem_file.seek(addr_start + i)
	mem_file.write(bytes(write_string, "ASCII"))

	# close files 
	maps_file.close()
	mem_file.close()

	# there is only one heap, so end
	break

# check
print("[*] Terminating.")