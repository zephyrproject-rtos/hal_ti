zephyr_library()

zephyr_include_directories(
  .
  inc_common
  inc_adapt
  trnspt_layer
)

zephyr_library_sources(
  trnspt_layer/commands.c
  trnspt_layer/fw_event_handle.c
  trnspt_layer/fw_event_if.c
  trnspt_layer/rx.c
  trnspt_layer/trnspt_if.c
  trnspt_layer/trnspt_thread.c
  trnspt_layer/txn_bus_drv.c
  utils/ip_utils.c
  utils/osi_common.c
  utils/w_queue.c
  utils/timer.c
  utils/event.c
  utils/errors.c
)
