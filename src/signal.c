//
// Created by wong on 10/27/18.
//

#include "signal.h"


static void signal_cb(evutil_socket_t fd, short events, void *arg) {
    TRANSOCKS_UNUSED(fd);
    TRANSOCKS_UNUSED(events);
    transocks_global_env *env = (transocks_global_env *) arg;
    if (event_base_loopbreak(env->eventBaseLoop) != 0)
        LOGE("fail to event_base_loopbreak");
}

int signal_init(transocks_global_env *env) {
    env->sigterm_ev = evsignal_new(env->eventBaseLoop, SIGTERM, signal_cb, env);
    env->sigint_ev = evsignal_new(env->eventBaseLoop, SIGINT, signal_cb, env);

    if (env->sigterm_ev == NULL || env->sigint_ev == NULL) {
        LOGE("fail to allocate evsignal");
        return -1;
    }

    if (evsignal_add(env->sigterm_ev, NULL) != 0) {
        LOGE("fail to add SIGTERM");
        return -1;
    }
    if (evsignal_add(env->sigint_ev, NULL) != 0) {
        LOGE("fail to add SIGINT");
        return -1;
    }

    return 0;
}

void signal_deinit(transocks_global_env *env) {
    if (env == NULL) return;
    if (env->sigint_ev != NULL) {
        evsignal_del(env->sigint_ev);
        TRANSOCKS_FREE(event_free, env->sigint_ev);
    }
    if (env->sigterm_ev != NULL) {
        evsignal_del(env->sigterm_ev);
        TRANSOCKS_FREE(event_free, env->sigterm_ev);
    }
}
