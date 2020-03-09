import os

include_files = 'tic.h,termcap.h,ncurses_defs,term.h,MKparametrized.sh,Caps.osf1r5,unctrl.h,Makefile.in,curses.h,curses.tail,MKkey_defs.sh,unctrl.h.in,MKterm.h.awk.in,curses.head,termcap.h.in,curses.wide,term_entry.h,Caps.hpux11,ncurses_cfg.hin,curses.h.in,Caps,nc_string.h,nc_tparm.h,panel.h,Caps.aix4,edit_cfg.sh,nc_mingw.h,nc_termios.h,ncurses_dll.h,config.h,ncurses_dll.h.in,MKterm.h.awk,parametrized.h,Makefile,menu.h,headers,ncurses_mingw.h,nc_panel.h,ncurses_def.h,hashsize.h,Caps.keys,ncurses_cfg.h,MKhashsize.sh,mf_common.h,hashed_db.h,capdefaults.c,form.h,eti.h,Caps.uwin,nc_alloc.h,MKncurses_def.sh'.split(',')

lib_files = 'libmenu.a,libpanel.a,libform.a,libform_g.a,libncurses_g.a,libpanel_g.a,libncurses++.a,libncurses.a,libmenu_g.a,libncurses++_g.a'.split(',')

if not os.path.exists('include'):
	os.makedirs('include')
	for file_name in include_files:
		try:
			os.rename(file_name, 'include/' + file_name)
		except:
			pass

if not os.path.exists('lib'):
	os.makedirs('lib')
	for file_name in lib_files:
		try:
			os.rename(file_name, 'lib/' + file_name)
		except:
			pass
