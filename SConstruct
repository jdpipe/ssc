#! python scons

env = Environment()

env['CC']="ccache gcc"
env['CXX']="ccache g++"
env.AppendUnique(CCFLAGS=["-Wall","-Wno-strict-aliasing"])
env.AppendUnique(CCFLAGS=["-g","-O3","-D__64BIT__","-fPIC"])
env.AppendUnique(CXXFLAGS=["-std=c++0x"])

subdirs = ['shared','nlopt','lpsolve','solarpilot','tcs','ssc']

Export('env')

objs = []
for s in subdirs:
	o = SConscript("%s/SConscript"%s)
	objs += o

env.SharedLibrary('ssc',objs)

SConscript('test/SConscript')

