#!/bin/sh

inet_dbg -s -u Cmdenv -c StoreAndForward --sim-time-limit=0.1s --cmdenv-redirect-output=true --record-eventlog=true &
inet_dbg -s -u Cmdenv -c CutthroughSwitching --sim-time-limit=0.1s --cmdenv-redirect-output=true --record-eventlog=true