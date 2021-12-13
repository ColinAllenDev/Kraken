#!/bin/sh
premake5 clean &
exec premake5 gmake2
