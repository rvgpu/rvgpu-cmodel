#! /usr/bin/env python3

import yaml
import os
import sys

def get_yaml_data(yaml_file):
    # Open yaml file
    file = open(yaml_file, "r", encoding = 'utf-8')
    file_data = file.read();
    file.close()

    # translate yaml data to dictionaries data
    # data = yaml.load(file_data, Loader=yaml.FullLoader)
    data = yaml.safe_load(file_data)

    return data

class test_generator:
    tc_counter = 0

    outf = ""

    def __init__(self, conf, fname):
        self.outf = open(fname, "w")
        self.outf.write("#include <gtest/gtest.h>\n")
        self.outf.write("#include \"unit/ut_insns.hpp\"\n")

    def __del__(self):
        self.outf.close()

    def process_testcase_inst(self, inst):
        if inst is None:
            return
        if isinstance(inst, list):
            for var in inst:
                self.outf.write("\tinsts.push_back(0x%08x);\n" % (var))

        if isinstance(inst, int):
            self.outf.write("\tinsts.push_back(0x%08x);\n" % (inst))

    def process_testcase_exec_in(self, indata):
        if indata is None:
            return

        self.outf.write("\tLoadInst();\n");
        if isinstance(indata, dict):
            for var in indata:
                self.outf.write("WRITE_REG(fetch.insn.%s(), %d);\n" % (var, indata[var]))

        if isinstance(indata, list):
            for vard in indata:
                for var in vard:
                    self.outf.write("\tWRITE_REG(fetch.insn.%s(), %d);\n" % (var, vard[var]))

    def process_testcase_exec_out(self, odata):
        if odata is None:
            return

        self.outf.write("\tExecuateInst();\n");
        if isinstance(odata, dict):
            for var in odata:
                self.outf.write("\tresult = READ_REG(fetch.insn.%s());\n" % (var))
                self.outf.write("\tEXPECT_EQ(result, %d);\n" % (odata[var]))

        if isinstance(odata, list):
            for vard in odata:
                for var in vard:
                    self.outf.write("\tresult = READ_REG(fetch.insn.%s());\n" % (var))
                    self.outf.write("\tEXPECT_EQ(result, %d);\n" % (vard[var]))

    def process_testcase_exec(self, exe):
        if exe is None:
            return

        if "in" in exe:
            self.process_testcase_exec_in(exe["in"])

        if "out" in exe:
            self.process_testcase_exec_out(exe["out"])

    def process_testcase(self, tcdict):
        if tcdict is None:
            return

        # write testcase function
        self.outf.write("\n")
        self.outf.write("TEST_F(ut_insns, generate_ut_%s_%d) {\n" % ("addi", self.tc_counter))
        self.outf.write("\tuint32_t result = 0;\n")

        tc = tcdict["testcase"]
        self.tc_counter += 1;
        if not isinstance(tc, list):
            return

        for var in tc:
            if "inst" in var:
                self.process_testcase_inst(var["inst"])
            if "exec" in var:
                self.process_testcase_exec(var["exec"])

        self.outf.write("}\n")
    def process_testsuite(self, ts):
        if ts is None:
            return

        if (isinstance(ts, list)):
            for tc in ts:
                self.process_testcase(tc)

        if (isinstance(ts, dict)):
            for tc in ts:
                self.process_testcase(ts[tc])

if __name__ == "__main__":
    source_dir = sys.argv[1]
    testname = sys.argv[2]
    yaml_path = os.path.join(source_dir, "%s.yaml" % (testname))

    configs = get_yaml_data(yaml_path)

    tgen = test_generator(configs, "ut_insns_gen_addi.cpp")

    if "testsuite" in configs:
        tgen.process_testsuite(configs["testsuite"])
