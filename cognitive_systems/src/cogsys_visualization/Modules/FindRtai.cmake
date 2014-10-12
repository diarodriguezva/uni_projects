include(FindPackageHandleStandardArgs)

file(
	GLOB
	RTAI_INCLUDE_PATHS
	$ENV{RTAIDIR}/include
	$ENV{HOME}/include
	/usr/local/include
	/usr/realtime/include
	/usr/include/rtai
	/usr/include
)

file(
	GLOB
	RTAI_LIBRARY_PATHS
	$ENV{RTAIDIR}/lib
	$ENV{HOME}/lib
	/usr/local/lib
	/usr/realtime/lib
	/usr/lib
)

find_path(
	RTAI_INCLUDE_DIRS
	NAMES
	rtai_lxrt.h
	HINTS
	${RTAI_INCLUDE_PATHS}
)

find_library(
	RTAI_LXRT_LIBRARY
	NAMES
	lxrt
	HINTS
	${RTAI_LIBRARY_PATHS}
)

set(
	RTAI_LIBRARIES
	${RTAI_LXRT_LIBRARY}
	rt
)

find_package_handle_standard_args(
	Rtai
	DEFAULT_MSG
	RTAI_INCLUDE_DIRS
	RTAI_LXRT_LIBRARY
)

mark_as_advanced(
	RTAI_INCLUDE_DIRS
	RTAI_LIBRARIES
	RTAI_LXRT_LIBRARY
) 
