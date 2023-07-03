#! /usr/bin/env python

import sys

srcpath = sys.argv[1]
instname = sys.argv[2]

tempfile = open(srcpath + "/" + "insn_template.cc", "r")
outfile = open(instname + ".cpp", "w")

data = tempfile.read();

data = data.replace("NAME", instname)
data = data.replace("OPCODE", " MATCH_" + instname.upper())

outfile.write(data)

tempfile.close()
outfile.close()
