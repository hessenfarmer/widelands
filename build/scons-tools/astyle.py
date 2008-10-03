import os
import SCons.Builder
import SCons.Action

# no version of astyle <=1.22 works correctly for us, so this list of strings is empty so far
DESIRABLE_VERSIONS=[]

def complain_astyle(target, source, env):
	print 'INFORMATION: astyle binary not found or wrong version (see above). Source indenting was not performed.'

def generate(env):
	env['ASTYLE']=find_astyle(env)

	if env['ASTYLE']!=None:
		env['ASTYLEFLAGS']='--mode=c --suffix=none --indent=tab=3 --indent-preprocessor --one-line=keep-statements --one-line=keep-blocks'
		env['ASTYLECOM']='$ASTYLE $ASTYLEFLAGS $SOURCES'
		env['BUILDERS']['astyle']=SCons.Builder.Builder(action=env['ASTYLECOM'])
	else:
		env['BUILDERS']['astyle']=SCons.Builder.Builder(action=env.Action(complain_astyle))

def find_astyle(env):
	binary=env.WhereIs('astyle')
	buggy_binary=env.WhereIs('buggy-astyle')

	if binary==None:
		print 'Searching for astyle:      not found. Cannot perform source indenting.'
	else:
		version=os.popen('LANG=C '+binary+' --version 2>&1 | cut -d" "  -f4').read().rstrip()

		if version in DESIRABLE_VERSIONS:
			print 'Searching for astyle:     ', binary
		else:
			if buggy_binary==None:
				print 'Searching for astyle:     ', binary
				print '                           WARNING: some astyle versions produce malformed indentation (see for example'
				print '                           [https://sourceforge.net/tracker/index.php?func=detail&aid=1642489&group_id=2319&atid=102319])'
				print '                           and are disabled whilst waiting for repair. If you really want to use it, execute'
				print '                           "cd /usr/bin && ln -s astyle buggy-astyle" and try again.'
			else:
				binary=buggy_binary

	return binary

def exists(env):
	if find_astyle(env)==None:
		return 0
	return 1

