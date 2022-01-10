# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.c.Debug:
/Users/stanislav/Desktop/c/Лабораторная\ 3/1/1/Debug/c:
	/bin/rm -f /Users/stanislav/Desktop/c/Лабораторная\ 3/1/1/Debug/c


PostBuild.c.Release:
/Users/stanislav/Desktop/c/Лабораторная\ 3/1/1/Release/c:
	/bin/rm -f /Users/stanislav/Desktop/c/Лабораторная\ 3/1/1/Release/c


PostBuild.c.MinSizeRel:
/Users/stanislav/Desktop/c/Лабораторная\ 3/1/1/MinSizeRel/c:
	/bin/rm -f /Users/stanislav/Desktop/c/Лабораторная\ 3/1/1/MinSizeRel/c


PostBuild.c.RelWithDebInfo:
/Users/stanislav/Desktop/c/Лабораторная\ 3/1/1/RelWithDebInfo/c:
	/bin/rm -f /Users/stanislav/Desktop/c/Лабораторная\ 3/1/1/RelWithDebInfo/c




# For each target create a dummy ruleso the target does not have to exist
