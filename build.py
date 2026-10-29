#!/usr/bin/env python3
"""Build this application with a MiNT cross compiler and external MiNTlib/GEMlib."""
from pathlib import Path
import argparse,subprocess,os
src=Path(__file__).resolve().parent
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--cc',default=os.environ.get('CC','m68k-atari-mint-gcc'))
p.add_argument('--mintlib',type=Path,required=True,help='MiNTlib source/build tree (include/ and build/m68020/)')
p.add_argument('--gemlib',type=Path,required=True,help='GEMlib tree with .lib68020-60/')
p.add_argument('--output',type=Path,default=src/'build')
a=p.parse_args();out=a.output.resolve();out.mkdir(parents=True,exist_ok=True)
lib=a.mintlib.resolve()/'build/m68020';gem=a.gemlib.resolve()
cc=[a.cc,'-isystem',str(a.mintlib.resolve()/'include')]
names='fracirc gem parser output gotcmd dcc file input scroll fonts dialogsu adaptrsc windows channels dhandler events sound vars ftalk vdi compat preferences irc_wire irc_users channelview connection history history_scroll'.split()
objs=[]
for n in names:
 o=out/(n+'.o');subprocess.run(cc+['-m68060','-msoft-float','-Os','-I'+str(gem),'-I'+str(src),'-include',str(src/'compat.h'),'-c',str(src/(n+'.c')),'-o',str(o)],check=True);objs.append(str(o))
subprocess.run(cc+['-m68060','-msoft-float','-nostdlib','-Wl,--stack,128k','-o',str(out/'FRACIRC.PRG'),str(lib/'crt0.o')]+objs+['-L'+str(gem/'.lib68020-60'),'-L'+str(lib),'-Wl,--start-group','-lgem','-lc','-lgcc','-Wl,--end-group'],check=True)
