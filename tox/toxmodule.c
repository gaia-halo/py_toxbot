
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <tox/tox.h>

#include <stdio.h>

// ToxError class
static PyObject *ToxError;

// Error messages
static const char *tox_err_options_new_strings[] = {
    "TOX_ERR_OPTIONS_NEW_OK",
    "TOX_ERR_OPTIONS_NEW_MALLOC"
};

static const char *tox_err_new_strings[] = {
    "TOX_ERR_NEW_OK",
    "TOX_ERR_NEW_NULL",
    "TOX_ERR_NEW_MALLOC",
    "TOX_ERR_NEW_PORT_ALLOC",
    "TOX_ERR_NEW_PROXY_BAD_TYPE",
    "TOX_ERR_NEW_PROXY_BAD_HOST",
    "TOX_ERR_NEW_PROXY_BAD_PORT",
    "TOX_ERR_NEW_PROXY_NOT_FOUND",
    "TOX_ERR_NEW_LOAD_ENCRYPTED",
    "TOX_ERR_NEW_LOAD_BAD_FORMAT"
};

static const char *tox_err_bootstrap_strings[] = {
    "TOX_ERR_BOOTSTRAP_OK",
    "TOX_ERR_BOOTSTRAP_NULL",
    "TOX_ERR_BOOTSTRAP_BAD_HOST",
    "TOX_ERR_BOOTSTRAP_BAD_PORT",
};

static const char *tox_err_set_info_strings[] = {
    "TOX_ERR_SET_INFO_OK",
    "TOX_ERR_SET_INFO_NULL",
    "TOX_ERR_SET_INFO_TOO_LONG",
};

static const char *tox_err_friend_add_strings[] = {
    "TOX_ERR_FRIEND_ADD_OK",
    "TOX_ERR_FRIEND_ADD_NULL",
    "TOX_ERR_FRIEND_ADD_TOO_LONG",
    "TOX_ERR_FRIEND_ADD_NO_MESSAGE",
    "TOX_ERR_FRIEND_ADD_OWN_KEY",
    "TOX_ERR_FRIEND_ADD_ALREADY_SENT",
    "TOX_ERR_FRIEND_ADD_BAD_CHECKSUM",
    "TOX_ERR_FRIEND_ADD_SET_NEW_NOSPAM",
    "TOX_ERR_FRIEND_ADD_MALLOC",
};

static const char *tox_err_friend_delete_strings[] = {
    "TOX_ERR_FRIEND_DELETE_OK",
    "TOX_ERR_FRIEND_DELETE_FRIENT_NOT_FOUND",
};

static const char *tox_err_friend_by_public_key_strings[] = {
    "TOX_ERR_FRIEND_BY_PUBLIC_KEY_OK",
    "TOX_ERR_FRIEND_BY_PUBLIC_KEY_NULL",
    "TOX_ERR_FRIEND_BY_PUBLIC_KEY_NOT_FOUND",
};

static const char *tox_err_friend_get_public_key_strings[] = {
    "TOX_ERR_FRIEND_GET_PUBLIC_KEY_OK",
    "TOX_ERR_FRIEND_GET_PUBLIC_KEY_FRIEND_NOT_FOUND",
};

static const char *tox_err_friend_get_last_online_strings[] = {
    "TOX_ERR_FRIEND_GET_LAST_ONLINE_OK",
    "TOX_ERR_FRIEND_GET_LAST_ONLINE_FRIEND_NOT_FOUND",
};

static const char *tox_err_friend_query_strings[] = {
    "TOX_ERR_FRIEND_QUERY_OK",
    "TOX_ERR_FRIEND_QUERY_NULL",
    "TOX_ERR_FRIEND_QUERY_FRIENT_NOT_FOUND",
};

static const char *tox_err_set_typing_strings[] = {
    "TOX_ERR_SET_TYPING_OK",
    "TOX_ERR_SET_TYPING_FRIENT_NOT_FOUND",
};

static const char *tox_err_friend_send_message_strings[] = {
    "TOX_ERR_FRIEND_SEND_MESSAGE_OK",
    "TOX_ERR_FRIEND_SEND_MESSAGE_NULL",
    "TOX_ERR_FRIEND_SEND_MESSAGE_FRIEND_NOT_FOUND",
    "TOX_ERR_FRIEND_SEND_MESSAGE_FRIEND_NOT_CONNECTED",
    "TOX_ERR_FRIEND_SEND_MESSAGE_SENDQ",
    "TOX_ERR_FRIEND_SEND_MESSAGE_TOO_LONG",
    "TOX_ERR_FRIEND_SEND_MESSAGE_EMPTY",
};

static const char *tox_err_file_control_strings[] = {
    "TOX_ERR_FILE_CONTROL_OK",
    "TOX_ERR_FILE_CONTROL_FRIEND_NOT_FOUND",
    "TOX_ERR_FILE_CONTROL_FRIEND_NOT_CONNECTED",
    "TOX_ERR_FILE_CONTROL_NOT_FOUND",
    "TOX_ERR_FILE_CONTROL_NOT_PAUSED",
    "TOX_ERR_FILE_CONTROL_DENIED",
    "TOX_ERR_FILE_CONTROL_ALREADY_PAUSED",
    "TOX_ERR_FILE_CONTROL_SENDQ",
};

static const char *tox_err_file_seek_strings[] = {
    "TOX_ERR_FILE_SEEK_OK",
    "TOX_ERR_FILE_SEEK_FRIEND_NOT_FOUND",
    "TOX_ERR_FILE_SEEK_FRIEND_NOT_CONNECTED",
    "TOX_ERR_FILE_SEEK_NOT_FOUND",
    "TOX_ERR_FILE_SEEK_DENIED",
    "TOX_ERR_FILE_SEEK_INVALID_POSITION",
    "TOX_ERR_FILE_SEEK_SENDQ",
};

static const char *tox_err_file_get_strings[] = {
    "TOX_ERR_FILE_GET_OK",
    "TOX_ERR_FILE_GET_NULL",
    "TOX_ERR_FILE_GET_FRIEND_NOT_FOUND",
    "TOX_ERR_FILE_GET_NOT_FOUND",
};

static const char *tox_err_file_send_strings[] = {
    "TOX_ERR_FILE_SEND_OK",
    "TOX_ERR_FILE_SEND_NULL",
    "TOX_ERR_FILE_SEND_FRIEND_NOT_FOUND",
    "TOX_ERR_FILE_SEND_FRIEND_NOT_CONNECTED",
    "TOX_ERR_FILE_SEND_NAME_TOO_LONG",
    "TOX_ERR_FILE_SEND_TOO_MANY",
};

static const char *tox_err_file_send_chunk_strings[] = {
    "TOX_ERR_FILE_SEND_CHUNK_OK",
    "TOX_ERR_FILE_SEND_CHUNK_NULL",
    "TOX_ERR_FILE_SEND_CHUNK_FRIEND_NOT_FOUND",
    "TOX_ERR_FILE_SEND_CHUNK_FRIEND_NOT_CONNECTED",
    "TOX_ERR_FILE_SEND_CHUNK_NOT_FOUND",
    "TOX_ERR_FILE_SEND_CHUNK_NOT_TRANSFERRING",
    "TOX_ERR_FILE_SEND_CHUNK_INVALID_LENGTH",
    "TOX_ERR_FILE_SEND_CHUNK_SENDQ",
    "TOX_ERR_FILE_SEND_CHUNK_WRONG_POSITION",
};

static const char *tox_err_conference_new_strings[] = {
    "TOX_ERR_CONFERENCE_NEW_OK",
    "TOX_ERR_CONFERENCE_NEW_INIT",
};

static const char *tox_err_conference_delete_strings[] = {
    "TOX_ERR_CONFERENCE_DELETE_OK",
    "TOX_ERR_CONFERENCE_DELETE_CONFERENCE_NOT_FOUND",
};

static const char *tox_err_conference_peer_query_strings[] = {
    "TOX_ERR_CONFERENCE_PEER_QUERY_OK",
    "TOX_ERR_CONFERENCE_PEER_QUERY_CONFERENCE_NOT_FOUND",
    "TOX_ERR_CONFERENCE_PEER_QUERY_PEER_NOT_FOUND",
    "TOX_ERR_CONFERENCE_PEER_QUERY_NO_CONNECTION",
};

static const char *tox_err_conference_set_max_offline_strings[] = {
    "TOX_ERR_CONFERENCE_SET_MAX_OFFLINE_OK",
    "TOX_ERR_CONFERENCE_SET_MAX_OFFLINE_CONFERENCE_NOT_FOUND",
};

static const char *tox_err_conference_invite_strings[] = {
    "TOX_ERR_CONFERENCE_INVITE_OK",
    "TOX_ERR_CONFERENCE_INVITE_CONFERENCE_NOT_FOUND",
    "TOX_ERR_CONFERENCE_INVITE_FAIL_SEND",
    "TOX_ERR_CONFERENCE_INVITE_NO_CONNECTION",
};

static const char *tox_err_conference_join_strings[] = {
    "TOX_ERR_CONFERENCE_JOIN_OK",
    "TOX_ERR_CONFERENCE_JOIN_INVALID_LENGTH",
    "TOX_ERR_CONFERENCE_JOIN_WRONG_TYPE",
    "TOX_ERR_CONFERENCE_JOIN_FRIEND_NOT_FOUND",
    "TOX_ERR_CONFERENCE_JOIN_DUPLICATE",
    "TOX_ERR_CONFERENCE_JOIN_INIT_FAIL",
    "TOX_ERR_CONFERENCE_JOIN_FAIL_SEND",
};

static const char *tox_err_conference_send_message_strings[] = {
    "TOX_ERR_CONFERENCE_SEND_MESSAGE_OK",
    "TOX_ERR_CONFERENCE_SEND_MESSAGE_CONFERENCE_NOT_FOUND",
    "TOX_ERR_CONFERENCE_SEND_MESSAGE_TOO_LONG",
    "TOX_ERR_CONFERENCE_SEND_MESSAGE_NO_CONNECTION",
    "TOX_ERR_CONFERENCE_SEND_MESSAGE_FAIL_SEND",
};

static const char *tox_err_conference_title_strings[] = {
    "TOX_ERR_CONFERENCE_TITLE_OK",
    "TOX_ERR_CONFERENCE_TITLE_CONFERENCE_NOT_FOUND",
    "TOX_ERR_CONFERENCE_TITLE_INVALID_LENGTH",
    "TOX_ERR_CONFERENCE_TITLE_FAIL_SEND",
};

static const char *tox_err_conference_get_type_strings[] = {
    "TOX_ERR_CONFERENCE_GET_TYPE_OK",
    "TOX_ERR_CONFERENCE_GET_TYPE_CONFERENCE_NOT_FOUND",
};

static const char *tox_err_conference_by_id_strings[] = {
    "TOX_ERR_CONFERENCE_BY_ID_OK",
    "TOX_ERR_CONFERENCE_BY_ID_NULL",
    "TOX_ERR_CONFERENCE_BY_ID_NOT_FOUND",
};

static const char *tox_err_friend_custom_packet_strings[] = {
    "TOX_ERR_FRIEND_CUSTOM_PACKET_OK",
    "TOX_ERR_FRIEND_CUSTOM_PACKET_NULL",
    "TOX_ERR_FRIEND_CUSTOM_PACKET_FRIEND_NOT_FOUND",
    "TOX_ERR_FRIEND_CUSTOM_PACKET_FRIEND_NOT_CONNECTED",
    "TOX_ERR_FRIEND_CUSTOM_PACKET_INVALID",
    "TOX_ERR_FRIEND_CUSTOM_PACKET_EMPTY",
    "TOX_ERR_FRIEND_CUSTOM_PACKET_TOO_LONG",
    "TOX_ERR_FRIEND_CUSTOM_PACKET_SENDQ",
};

static const char *tox_err_get_port_strings[] = {
    "TOX_ERR_GET_PORT_OK",
    "TOX_ERR_GET_PORT_NOT_BOUND",
};

// Tox enumerates
int tox_enumerates_values[] = {
    // Tox_User_Status
    TOX_USER_STATUS_NONE, TOX_USER_STATUS_AWAY, TOX_USER_STATUS_BUSY,
    // Tox_Message_Type
    TOX_MESSAGE_TYPE_NORMAL, TOX_MESSAGE_TYPE_ACTION,
    // Tox_Proxy_Type
    TOX_PROXY_TYPE_NONE, TOX_PROXY_TYPE_HTTP, TOX_PROXY_TYPE_SOCKS5,
    // Tox_Savedata_Type
    TOX_SAVEDATA_TYPE_NONE, TOX_SAVEDATA_TYPE_TOX_SAVE,
    TOX_SAVEDATA_TYPE_SECRET_KEY,
    // Tox_Log_Level
    TOX_LOG_LEVEL_TRACE, TOX_LOG_LEVEL_DEBUG, TOX_LOG_LEVEL_INFO,
    TOX_LOG_LEVEL_WARNING, TOX_LOG_LEVEL_ERROR,
    // Tox_Connection
    TOX_CONNECTION_NONE, TOX_CONNECTION_TCP, TOX_CONNECTION_UDP,
    // Tox_File_Kind
    TOX_FILE_KIND_DATA, TOX_FILE_KIND_AVATAR,
    // Tox_File_Control
    TOX_FILE_CONTROL_RESUME, TOX_FILE_CONTROL_PAUSE, TOX_FILE_CONTROL_CANCEL,
    // Tox_Conference_Type
    TOX_CONFERENCE_TYPE_TEXT, TOX_CONFERENCE_TYPE_AV,
};

// Tox enumerates strings
const char *tox_enumerates_strings[] = {
    // Tox_User_Status
    "USER_STATUS_NONE", "USER_STATUS_AWAY", "USER_STATUS_BUSY",
    // Tox_Message_Type
    "MESSAGE_TYPE_NORMAL", "MESSAGE_TYPE_ACTION",
    // Tox_Proxy_Type
    "PROXY_TYPE_NONE", "PROXY_TYPE_HTTP", "PROXY_TYPE_SOCKS5",
    // Tox_Savedata_Type
    "SAVEDATA_TYPE_NONE", "SAVEDATA_TYPE_TOX_SAVE", "SAVEDATA_TYPE_SECRET_KEY",
    // Tox_Log_Level
    "LOG_LEVEL_TRACE", "LOG_LEVEL_DEBUG", "LOG_LEVEL_INFO",
    "LOG_LEVEL_WARNING", "LOG_LEVEL_ERROR",
    // Tox_Connection
    "CONNECTION_NONE", "CONNECTION_TCP", "CONNECTION_UDP",
    // Tox_File_Kind
    "FILE_KIND_DATA", "FILE_KIND_AVATAR",
    // Tox_File_Control
    "FILE_CONTROL_RESUME", "FILE_CONTROL_PAUSE", "FILE_CONTROL_CANCEL",
    // Tox_Conference_Type
    "CONFERENCE_TYPE_TEXT", "CONFERENCE_TYPE_AV",
};

// Num Tox enumerates
const int NUM_ENUMERATES = sizeof(tox_enumerates_values)/sizeof(int);

/* Return the callback from the input arguments */
static PyObject *
get_callback(PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"callback", NULL};
    PyObject *callback;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist, &callback))
        return NULL;

    if (callback != Py_None) {
        // Verify its callable
        if (!PyCallable_Check(callback)) {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }
        Py_INCREF(callback);
    }
    return callback;
}

/////////////// Options object definition /////////////////////////////////////

// Options class
typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
    struct Tox_Options *options;
    PyObject *proxy_host;
    PyObject *savedata;
    PyObject *log_cb;
} OptionsObject;

/* Logging callback for the new tox instance. */
static void
Tox_log_callback(Tox *tox, Tox_Log_Level level, const char *file,
    uint32_t line, const char *func, const char *message, void *user_data);

/* Options instance destructor
   The Options instance has to be finished with tox_options_free.
   Remove as well the reference to the savedata object.
   */
static void
Options_dealloc(OptionsObject *self)
{
    Py_XDECREF(self->proxy_host);
    Py_XDECREF(self->savedata);
    Py_XDECREF(self->log_cb);
    if (self->options) {
        tox_options_free(self->options);
    }
    Py_TYPE(self)->tp_free((PyObject *) self);
}

/* Options instance constructor
   Constructor of an Options instance using tox_options_new.
   */
static PyObject *
Options_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    OptionsObject *self;
    Tox_Err_Options_New tox_options_err;

    self = (OptionsObject *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->savedata = NULL;
        self->options = tox_options_new(&tox_options_err);
        if (tox_options_err != TOX_ERR_OPTIONS_NEW_OK) {
            // An error occurred
            // Set the exception
            PyErr_SetString(
                ToxError, tox_err_options_new_strings[tox_options_err]);
            // If an instance was created and returned, clean it
            if (self->options) {
                tox_options_free(self->options);
            }
            Py_DECREF(self);
            return NULL;
        }
    }
    return (PyObject *) self;
}

static int
Options_init(OptionsObject *self)
{
    // Initialize members
    self->proxy_host = NULL;
    self->savedata = NULL;
    self->log_cb = NULL;

    // Initialize the options object
    tox_options_default(self->options);

    return 0;
}

/* Get the options attribute ipv6_enabled */
static PyObject *
Options_get_ipv6_enabled(OptionsObject *self)
{
    return PyBool_FromLong(tox_options_get_ipv6_enabled(self->options));
}

/* Set the options attribute ipv6_enabled */
static PyObject *
Options_set_ipv6_enabled(OptionsObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"ipv6_enabled", NULL};
    bool enabled;

    // Parse the input arguments (data)
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "p", kwlist, &enabled))
        return NULL;

    // Set the attribute
    tox_options_set_ipv6_enabled(self->options, enabled);
    Py_RETURN_NONE;
}

/* Get the options attribute udp_enabled */
static PyObject *
Options_get_udp_enabled(OptionsObject *self)
{
    return PyBool_FromLong(tox_options_get_udp_enabled(self->options));
}

/* Set the options attribute udp_enabled */
static PyObject *
Options_set_udp_enabled(OptionsObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"udp_enabled", NULL};
    bool enabled;

    // Parse the input arguments (data)
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "p", kwlist, &enabled))
        return NULL;

    // Set the attribute
    tox_options_set_udp_enabled(self->options, enabled);
    Py_RETURN_NONE;
}

/* Get the options attribute local_discovery_enabled */
static PyObject *
Options_get_local_discovery_enabled(OptionsObject *self)
{
    return PyBool_FromLong(
        tox_options_get_local_discovery_enabled(self->options));
}

/* Set the options attribute local_discovery_enabled */
static PyObject *
Options_set_local_discovery_enabled(
    OptionsObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"local_discovery_enabled", NULL};
    bool enabled;

    // Parse the input arguments (data)
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "p", kwlist, &enabled))
        return NULL;

    // Set the attribute
    tox_options_set_local_discovery_enabled(self->options, enabled);
    Py_RETURN_NONE;
}

/* Get the proxy options attributes */
static PyObject *
Options_get_proxy(OptionsObject *self)
{
    return Py_BuildValue("isH",
        tox_options_get_proxy_type(self->options),
        tox_options_get_proxy_host(self->options),
        tox_options_get_proxy_port(self->options));
}

/* Set the proxy options attributes */
static PyObject *
Options_set_proxy(OptionsObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"proxy_type", "proxy_host", "proxy_port", NULL};
    Tox_Proxy_Type type;
    PyObject *proxy_host = NULL, *tmp;
    const char *str_proxy_host;
    uint16_t proxy_port = 0;

    // Parse the input arguments (data)
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i|O!H", kwlist, &type,
        &PyUnicode_Type, &proxy_host, &proxy_port))
    {
        return NULL;
    }

    // Check the proxy type value
    if (type < TOX_PROXY_TYPE_NONE || type > TOX_PROXY_TYPE_SOCKS5) {
        PyErr_SetString(PyExc_ValueError,  "wrong value for proxy type");
        return NULL;
    }

    // Check that if the proxy type is not None, a proxy host must be given
    if (type != TOX_PROXY_TYPE_NONE && !proxy_host) {
        PyErr_SetString(PyExc_ValueError,  "proxy host not specified");
        return NULL;
    }

    // Keep a reference to the proxy_host
    if (proxy_host) {
        tmp = self->proxy_host;
        Py_INCREF(proxy_host);
        self->proxy_host = proxy_host;
        Py_XDECREF(tmp);

        // Get the proxy host from the string object
        str_proxy_host = PyUnicode_AsUTF8(proxy_host);
        if (!str_proxy_host)
            return NULL;

        // Set the proxy host
        tox_options_set_proxy_host(self->options, str_proxy_host);
    }

    // Set the proxy type and port
    tox_options_set_proxy_type(self->options, type);
    tox_options_set_proxy_port(self->options, proxy_port);
    Py_RETURN_NONE;
}

/* Get the options attribute start_port */
static PyObject *
Options_get_start_port(OptionsObject *self)
{
    return PyLong_FromLong(tox_options_get_start_port(self->options));
}

/* Set the options attribute start_port */
static PyObject *
Options_set_start_port(OptionsObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"start_port", NULL};
    uint16_t start_port;

    // Parse the input arguments (data)
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "H", kwlist, &start_port))
        return NULL;

    // Set the attribute
    tox_options_set_start_port(self->options, start_port);
    Py_RETURN_NONE;
}

/* Get the options attribute end_port */
static PyObject *
Options_get_end_port(OptionsObject *self)
{
    return PyLong_FromLong(tox_options_get_end_port(self->options));
}

/* Set the options attribute end_port */
static PyObject *
Options_set_end_port(OptionsObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"end_port", NULL};
    uint16_t end_port;

    // Parse the input arguments (data)
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "H", kwlist, &end_port))
        return NULL;

    // Set the attribute
    tox_options_set_end_port(self->options, end_port);
    Py_RETURN_NONE;
}

/* Get the options attribute tcp_port */
static PyObject *
Options_get_tcp_port(OptionsObject *self)
{
    return PyLong_FromLong(tox_options_get_tcp_port(self->options));
}

/* Set the options attribute tcp_port */
static PyObject *
Options_set_tcp_port(OptionsObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"tcp_port", NULL};
    uint16_t tcp_port;

    // Parse the input arguments (data)
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "H", kwlist, &tcp_port))
        return NULL;

    // Set the attribute
    tox_options_set_tcp_port(self->options, tcp_port);
    Py_RETURN_NONE;
}

/* Get the options attribute hole_punching_enabled */
static PyObject *
Options_get_hole_punching_enabled(OptionsObject *self)
{
    return PyBool_FromLong(
        tox_options_get_hole_punching_enabled(self->options));
}

/* Set the options attribute hole_punching_enabled */
static PyObject *
Options_set_hole_punching_enabled(
    OptionsObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"hole_punching_enabled", NULL};
    bool enabled;

    // Parse the input arguments (data)
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "p", kwlist, &enabled))
        return NULL;

    // Set the attribute
    tox_options_set_hole_punching_enabled(self->options, enabled);
    Py_RETURN_NONE;
}

/* Get the options attribute savedata_type */
static PyObject *
Options_get_savedata(OptionsObject *self)
{
    return Py_BuildValue("iy#",
        tox_options_get_savedata_type(self->options),
        tox_options_get_savedata_data(self->options),
        tox_options_get_savedata_length(self->options));
}

/* Set the options attribute savedata_type */
static PyObject *
Options_set_savedata(OptionsObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"type", "data", NULL};
    Tox_Savedata_Type type;
    PyObject *data = NULL, *tmp;
    char *str_data;
    size_t length;

    // Parse the input arguments
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i|O!", kwlist, &type,
        &PyBytes_Type, &data))
    {
        return NULL;
    }

    // Check the savedata type value
    if (type < TOX_SAVEDATA_TYPE_NONE || type > TOX_SAVEDATA_TYPE_SECRET_KEY) {
        PyErr_SetString(PyExc_ValueError,  "wrong value for data type");
        return NULL;
    }

    // Check that if the data type is not None, some data must be given
    if (type != TOX_SAVEDATA_TYPE_NONE && !data) {
        PyErr_SetString(PyExc_ValueError,  "data not specified");
        return NULL;
    }

    // Keep a reference to the savedata
    if (data) {
        tmp = self->savedata;
        Py_INCREF(data);
        self->savedata = data;
        Py_XDECREF(tmp);

        // Get the data from the bytes object
        if (PyBytes_AsStringAndSize(data, &str_data, &length))
            return NULL;

        // Set the savedata
        tox_options_set_savedata_length(self->options, length);
        tox_options_set_savedata_data(self->options, str_data, length);
    }

    // Set the savedata type
    tox_options_set_savedata_type(self->options, type);
    Py_RETURN_NONE;
}

/* Return the log callback */
static PyObject *
Options_get_log_callback(OptionsObject *self, PyObject *args, PyObject *kwds)
{
    if (self->log_cb) {
        Py_INCREF(self->log_cb);
        return self->log_cb;
    } else {
        Py_RETURN_NONE;
    }
}

/* Set the log callback */
static PyObject *
Options_set_log_callback(OptionsObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->log_cb);
    if (cb == Py_None) {
        self->log_cb = NULL;
        tox_options_set_log_callback(self->options, NULL);
    } else {
        self->log_cb = cb;
        tox_options_set_log_callback(self->options, Tox_log_callback);
    }
    Py_RETURN_NONE;
}

/* Definition of Options methods. */
static PyMethodDef Options_methods[] = {
    {"get_ipv6_enabled", (PyCFunction) Options_get_ipv6_enabled, METH_NOARGS,
     "Get the options attribute ipv6_enabled"},
    {"set_ipv6_enabled", (PyCFunction) Options_set_ipv6_enabled,
     METH_VARARGS | METH_KEYWORDS, "Set the options attribute ipv6_enabled"},
    {"get_udp_enabled", (PyCFunction) Options_get_udp_enabled, METH_NOARGS,
     "Get the options attribute udp_enabled"},
    {"set_udp_enabled", (PyCFunction) Options_set_udp_enabled,
     METH_VARARGS | METH_KEYWORDS, "Set the options attribute udp_enabled"},
    {"get_local_discovery_enabled",
     (PyCFunction) Options_get_local_discovery_enabled, METH_NOARGS,
     "Get the options attribute local_discovery_enabled"},
    {"set_local_discovery_enabled",
     (PyCFunction) Options_set_local_discovery_enabled,
     METH_VARARGS | METH_KEYWORDS,
     "Set the options attribute local_discovery_enabled"},
    {"get_proxy", (PyCFunction) Options_get_proxy, METH_NOARGS,
     "Get the proxy options attribute"},
    {"set_proxy", (PyCFunction) Options_set_proxy,
     METH_VARARGS | METH_KEYWORDS, "Set the proxy options attribute"},
    {"get_start_port", (PyCFunction) Options_get_start_port, METH_NOARGS,
     "Get the options attribute start_port"},
    {"set_start_port", (PyCFunction) Options_set_start_port,
     METH_VARARGS | METH_KEYWORDS, "Set the options attribute start_port"},
    {"get_end_port", (PyCFunction) Options_get_end_port, METH_NOARGS,
     "Get the options attribute end_port"},
    {"set_end_port", (PyCFunction) Options_set_end_port,
     METH_VARARGS | METH_KEYWORDS, "Set the options attribute end_port"},
    {"get_tcp_port", (PyCFunction) Options_get_tcp_port, METH_NOARGS,
     "Get the options attribute tcp_port"},
    {"set_tcp_port", (PyCFunction) Options_set_tcp_port,
     METH_VARARGS | METH_KEYWORDS, "Set the options attribute tcp_port"},
    {"get_hole_punching_enabled",
     (PyCFunction) Options_get_hole_punching_enabled, METH_NOARGS,
     "Get the options attribute hole_punching_enabled"},
    {"set_hole_punching_enabled",
     (PyCFunction) Options_set_hole_punching_enabled,
     METH_VARARGS | METH_KEYWORDS,
     "Set the options attribute hole_punching_enabled"},
    {"get_savedata", (PyCFunction) Options_get_savedata, METH_NOARGS,
     "Get the savedata options attributes"},
    {"set_savedata", (PyCFunction) Options_set_savedata,
     METH_VARARGS | METH_KEYWORDS, "Set the savedata options attribute"},
    {"get_log_callback", (PyCFunction) Options_get_log_callback, METH_NOARGS,
     "Return the log callback"},
    {"set_log_callback", (PyCFunction) Options_set_log_callback,
     METH_VARARGS | METH_KEYWORDS, "Set the log callback"},
    {NULL}  /* Sentinel */
};

// Options type
static PyTypeObject OptionsType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "tox.Options",
    .tp_doc = "Options for Tox",
    .tp_basicsize = sizeof(OptionsObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = Options_new,
    .tp_dealloc = (destructor) Options_dealloc,
    .tp_methods = Options_methods,
};

////////////////////////// Tox Object definition //////////////////////////////

// Tox class
typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
    Tox *tox;
    PyObject *log_cb;
    PyObject *self_connection_status_cb;
    PyObject *friend_name_cb;
    PyObject *friend_status_message_cb;
    PyObject *friend_status_cb;
    PyObject *friend_connection_status_cb;
    PyObject *friend_typing_cb;
    PyObject *friend_read_receipt_cb;
    PyObject *friend_message_cb;
    PyObject *friend_request_cb;
    PyObject *file_recv_control_cb;
    PyObject *file_chunk_request_cb;
    PyObject *file_recv_cb;
    PyObject *file_recv_chunk_cb;
    PyObject *conference_invite_cb;
    PyObject *conference_connected_cb;
    PyObject *conference_message_cb;
    PyObject *conference_title_cb;
    PyObject *conference_peer_name_cb;
    PyObject *conference_peer_list_changed_cb;
    PyObject *friend_lossy_packet_cb;
    PyObject *friend_lossless_packet_cb;
} ToxObject;

/* Logging callback for the new tox instance. */
static void
Tox_log_callback(Tox *tox, Tox_Log_Level level, const char *file,
    uint32_t line, const char *func, const char *message, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->log_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue(
            "OisIss", self, level, file, line, func, message);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->log_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when our connection status changes. */
static void
Tox_self_connection_status_callback(
    Tox *tox, Tox_Connection connection_status, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->self_connection_status_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("Oi", self, connection_status);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->self_connection_status_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback to inform of a friend's name. */
static void
Tox_friend_name_callback(Tox *tox, uint32_t friend_number,
    const uint8_t *name, size_t length, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->friend_name_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIs#", self, friend_number, name, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->friend_name_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback to inform of a friend's status message. */
static void
Tox_friend_status_message_callback(Tox *tox, uint32_t friend_number,
    const uint8_t *message, size_t length, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->friend_status_message_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIs#", self, friend_number, message, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->friend_status_message_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback to inform of a friend's status. */
static void
Tox_friend_status_callback(Tox *tox, uint32_t friend_number,
    Tox_User_Status status, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->friend_status_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIi", self, friend_number, status);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->friend_status_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback to inform of a friend's connection status. */
static void
Tox_friend_connection_status_callback(Tox *tox, uint32_t friend_number,
    Tox_Connection connection_status, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->friend_connection_status_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIi", self, friend_number, connection_status);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(
            self->friend_connection_status_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback to inform of a friend's typing status. */
static void
Tox_friend_typing_callback(
    Tox *tox, uint32_t friend_number, bool is_typing, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->friend_typing_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue(
            "OIN", self, friend_number, PyBool_FromLong(is_typing));
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->friend_typing_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback to inform of a received message read receipt. */
static void
Tox_friend_read_receipt_callback(
    Tox *tox, uint32_t friend_number, uint32_t message_id, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->friend_read_receipt_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OII", self, friend_number, message_id);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->friend_read_receipt_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when a friend request is received. */
static void
Tox_friend_request_callback(Tox *tox, const uint8_t *public_key,
    const uint8_t *message, size_t length, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->friend_request_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("Oy#s#", self, public_key,
            TOX_PUBLIC_KEY_SIZE, message, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->friend_request_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when a friend message is received. */
static void
Tox_friend_message_callback(Tox *tox, uint32_t friend_number,
    Tox_Message_Type type, const uint8_t *message, size_t length,
    void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->friend_message_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIis#", self, friend_number, type, message,
            length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->friend_message_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when a file control is received. */
static void
Tox_file_recv_control_callback(Tox *tox, uint32_t friend_number,
    uint32_t file_number, Tox_File_Control control, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->file_recv_control_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIIi", self, friend_number, file_number,
            control);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->file_recv_control_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when a friend requests a chunk of data. */
static void
Tox_file_chunk_request_callback(Tox *tox, uint32_t friend_number,
    uint32_t file_number, uint64_t position, size_t length, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->file_chunk_request_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIILI", self, friend_number, file_number,
            position, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->file_chunk_request_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when a file is received. */
static void
Tox_file_recv_callback(Tox *tox, uint32_t friend_number, uint32_t file_number,
    uint32_t kind, uint64_t file_size, const uint8_t *filename,
    size_t filename_length, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->file_recv_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIIILs#", self, friend_number, file_number,
            kind, file_size, filename, filename_length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->file_recv_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when a file chunk is received. */
static void
Tox_file_recv_chunk_callback(Tox *tox, uint32_t friend_number,
    uint32_t file_number, uint64_t position, const uint8_t *data,
    size_t length, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->file_recv_chunk_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIILy#", self, friend_number, file_number,
            position, data, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->file_recv_chunk_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when a friend invites us to a conference. */
static void
Tox_conference_invite_callback(Tox *tox, uint32_t friend_number,
    Tox_Conference_Type type, const uint8_t *cookie, size_t length,
    void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->conference_invite_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue(
            "OIiy#", self, friend_number, type, cookie, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->conference_invite_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when a we are finally connected to a conference. */
static void
Tox_conference_connected_callback(
    Tox *tox, uint32_t conference_number, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->conference_connected_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OI", self, conference_number);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->conference_connected_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when a message from a conference is received. */
static void
Tox_conference_message_callback(
    Tox *tox, uint32_t conference_number, uint32_t peer_number,
    Tox_Message_Type type, const uint8_t *message, size_t length,
    void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->conference_message_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIIis#", self, conference_number,
            peer_number, type, message, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->conference_message_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Callback executed when the title of a conference is changed. */
static void
Tox_conference_title_callback(
    Tox *tox, uint32_t conference_number, uint32_t peer_number,
    const uint8_t *title, size_t length, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->conference_title_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIIs#", self, conference_number, peer_number,
            title, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->conference_title_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* This event is triggered when a peer changes their name. */
static void
Tox_conference_peer_name_callback(
    Tox *tox, uint32_t conference_number, uint32_t peer_number,
    const uint8_t *name, size_t length, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->conference_peer_name_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIIs#", self, conference_number, peer_number,
            name, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(self->conference_peer_name_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* This event is triggered when a peer joins or leaves the conference. */
static void
Tox_conference_peer_list_changed_callback(
    Tox *tox, uint32_t conference_number, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->conference_peer_name_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OI", self, conference_number);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(
            self->conference_peer_list_changed_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* This event is triggered when we receive a lossy packet from a friend. */
static void
Tox_friend_lossy_packet_callback(Tox *tox, uint32_t friend_number,
    const uint8_t *data, size_t length, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->friend_lossy_packet_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIy#", self, friend_number, data, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(
            self->friend_lossy_packet_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* This event is triggered when we receive a lossless packet from a friend. */
static void
Tox_friend_lossless_packet_callback(Tox *tox, uint32_t friend_number,
    const uint8_t *data, size_t length, void *user_data)
{
    ToxObject *self = (ToxObject *)user_data;
    PyObject *arglist;
    PyObject *result;

    // If a callback is given, call it
    if (self->friend_lossless_packet_cb) {
        // Prepare the arguments for the callback
        arglist = Py_BuildValue("OIy#", self, friend_number, data, length);
        if (!arglist) {
            PyErr_PrintEx(0);
            return;
        }

        // Call the user callback
        result = PyObject_CallObject(
            self->friend_lossless_packet_cb, arglist);
        Py_DECREF(arglist);
        if (!result) {
            // An error occurred in the user callback
            PyErr_PrintEx(0);
        } else {
            Py_DECREF(result);
        }
    }
}

/* Tox instance destructor
   The Tox instance has to be finished with tox_kill
   */
static void
Tox_dealloc(ToxObject *self)
{
    Py_XDECREF(self->log_cb);
    Py_XDECREF(self->self_connection_status_cb);
    Py_XDECREF(self->friend_name_cb);
    Py_XDECREF(self->friend_status_message_cb);
    Py_XDECREF(self->friend_status_cb);
    Py_XDECREF(self->friend_connection_status_cb);
    Py_XDECREF(self->friend_typing_cb);
    Py_XDECREF(self->friend_read_receipt_cb);
    Py_XDECREF(self->friend_request_cb);
    Py_XDECREF(self->friend_message_cb);
    Py_XDECREF(self->file_recv_control_cb);
    Py_XDECREF(self->file_chunk_request_cb);
    Py_XDECREF(self->file_recv_cb);
    Py_XDECREF(self->file_recv_chunk_cb);
    Py_XDECREF(self->conference_invite_cb);
    Py_XDECREF(self->conference_connected_cb);
    Py_XDECREF(self->conference_message_cb);
    Py_XDECREF(self->conference_title_cb);
    Py_XDECREF(self->conference_peer_name_cb);
    Py_XDECREF(self->conference_peer_list_changed_cb);
    Py_XDECREF(self->friend_lossy_packet_cb);
    Py_XDECREF(self->friend_lossless_packet_cb);
    if (self->tox) {
        tox_kill(self->tox);
    }
    Py_TYPE(self)->tp_free((PyObject *) self);
}

/* Tox instance constructor
   Constructor of a Tox instance using tox_new.
   If an Options instance is given, use it to create the Tox instance.
   Otherwise, use the options by default.
   */
static PyObject *
Tox_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ToxObject *self;
    static char *kwlist[] = {"options", NULL};
    OptionsObject *options = NULL;
    Tox_Err_New tox_new_err;

    // Parse the input arguments, an optional 'options' parameter is expected
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O!", kwlist,
        &OptionsType, &options))
    {
        return NULL;
    }

    // Construct the Tox instance
    self = (ToxObject *) type->tp_alloc(type, 0);
    if (self != NULL) {
        if (options) {
            // If input options were given, use them to build the tox instance
            // Copy the log callback and set the user_data
            self->log_cb = NULL;
            if (options->log_cb) {
                tox_options_set_log_user_data(options->options, self);
                Py_INCREF(options->log_cb);
                self->log_cb = options->log_cb;
            }
            self->tox = tox_new(options->options, &tox_new_err);
        } else {
            // No input options given, use the default options
            self->tox = tox_new(NULL, &tox_new_err);
        }

        // Check if Tox was actually created
        if (tox_new_err != TOX_ERR_NEW_OK) {
            // An error occurred
            // Set the exception
            PyErr_SetString(ToxError, tox_err_new_strings[tox_new_err]);
            // If an instance was created and returned, clean it
            if (self->tox) {
                tox_kill(self->tox);
            }
            if (self->log_cb) {
                Py_DECREF(self->log_cb);
            }
            Py_DECREF(self);
            return NULL;
        }
    }
    return (PyObject *) self;
}

static int
Tox_init(ToxObject *self, PyObject *args, PyObject *kwds)
{
    // Initialize the python callbacks to Null
    self->log_cb = NULL;
    self->self_connection_status_cb = NULL;
    self->friend_name_cb = NULL;
    self->friend_status_message_cb = NULL;
    self->friend_status_cb = NULL;
    self->friend_connection_status_cb = NULL;
    self->friend_typing_cb = NULL;
    self->friend_read_receipt_cb = NULL;
    self->friend_request_cb = NULL;
    self->friend_message_cb = NULL;
    self->file_recv_control_cb = NULL;
    self->file_chunk_request_cb = NULL;
    self->file_recv_cb = NULL;
    self->file_recv_chunk_cb = NULL;
    self->conference_invite_cb = NULL;
    self->conference_connected_cb = NULL;
    self->conference_message_cb = NULL;
    self->conference_title_cb = NULL;
    self->conference_peer_name_cb = NULL;
    self->conference_peer_list_changed_cb = NULL;
    self->friend_lossy_packet_cb = NULL;
    self->friend_lossless_packet_cb = NULL;
    return 0;
}


/* Bootstrap to the DHT network */
static PyObject *
Tox_bootstrap(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"host", "port", "public_key", NULL};
    const char *host;
    uint16_t port;
    const char *public_key;
    size_t public_key_size;
    Tox_Err_Bootstrap tox_err_bootstrap;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "sHy#", kwlist, &host, &port,
        &public_key, &public_key_size))
    {
        return NULL;
    }

    // Check that the key has the valid length
    if (public_key_size != TOX_PUBLIC_KEY_SIZE) {
        PyErr_SetString(PyExc_ValueError, "public key wrong length");
        return NULL;
    }

    // Bootstrap
    if (!tox_bootstrap(self->tox, host, port, public_key, &tox_err_bootstrap))
    {
        // Error, raise a Tox exception
        PyErr_SetString(
            ToxError, tox_err_bootstrap_strings[tox_err_bootstrap]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Add additional host:port pair as TCP relay */
static PyObject *
Tox_add_tcp_relay(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"host", "port", "public_key", NULL};
    const char *host;
    uint16_t port;
    const char *public_key;
    size_t public_key_size;
    Tox_Err_Bootstrap tox_err_bootstrap;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "sHy#", kwlist, &host, &port,
        &public_key, &public_key_size))
    {
        return NULL;
    }

    // Check that the key has the valid length
    if (public_key_size != TOX_PUBLIC_KEY_SIZE) {
        PyErr_SetString(PyExc_ValueError, "public key wrong length");
        return NULL;
    }

    // Add the relay
    if (!tox_add_tcp_relay(
        self->tox, host, port, public_key, &tox_err_bootstrap))
    {
        // Error, raise a Tox exception
        PyErr_SetString(
            ToxError, tox_err_bootstrap_strings[tox_err_bootstrap]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Set the callback triggered by updates in our connection status */
static PyObject *
Tox_callback_self_connection_status(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->self_connection_status_cb);
    if (cb == Py_None) {
        self->self_connection_status_cb = NULL;
        tox_callback_self_connection_status(self->tox, NULL);
    } else {
        self->self_connection_status_cb = cb;
        tox_callback_self_connection_status(
            self->tox, Tox_self_connection_status_callback);
    }
    Py_RETURN_NONE;
}

/* Get the savedata bytes string */
static PyObject *
Tox_get_savedata(ToxObject *self)
{
    PyObject *savedata_bytes;
    size_t size = tox_get_savedata_size(self->tox);
    uint8_t *savedata = malloc(size);
    if (!savedata) {
        return PyErr_NoMemory();
    }

    // Obtain the savedata string
    tox_get_savedata(self->tox, savedata);

    // Build a bytes object with the savedata
    savedata_bytes = PyBytes_FromStringAndSize(savedata, size);
    free(savedata);
    return savedata_bytes;
}

/* Check Tox events. */
static PyObject *
Tox_iterate(ToxObject *self)
{
    tox_iterate(self->tox, self);
    Py_RETURN_NONE;
}

/* Return the recommended iteration interval to use for optimal performance. */
static PyObject *
Tox_iteration_interval(ToxObject *self)
{
    return PyLong_FromLong(tox_iteration_interval(self->tox));
}

/* Return the self Tox address. */
static PyObject *
Tox_self_get_address(ToxObject *self)
{
    uint8_t address[TOX_ADDRESS_SIZE];

    // Obtain the address
    tox_self_get_address(self->tox, address);

    // Put the address in a python bytes object
    return PyBytes_FromStringAndSize(address, TOX_ADDRESS_SIZE);
}

/* Set the 4-byte nospam part of the address. */
static PyObject *
Tox_self_set_nospam(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"nospam", NULL};
    uint32_t nospam;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &nospam))
        return NULL;

    // Set the nospam
    tox_self_set_nospam(self->tox, nospam);
    Py_RETURN_NONE;
}

/* Get the 4-byte nospam part of the address. */
static PyObject *
Tox_self_get_nospam(ToxObject *self)
{
    return PyLong_FromLong(tox_self_get_nospam(self->tox));
}

/* Get the Tox Public Key. */
static PyObject *
Tox_self_get_public_key(ToxObject *self)
{
    uint8_t public_key[TOX_PUBLIC_KEY_SIZE];

    // Obtain the public key
    tox_self_get_public_key(self->tox, public_key);

    // Put the key in a python bytes object
    return PyBytes_FromStringAndSize(public_key, TOX_PUBLIC_KEY_SIZE);
}

/* Get the Tox Secret Key. */
static PyObject *
Tox_self_get_secret_key(ToxObject *self)
{
    uint8_t secret_key[TOX_SECRET_KEY_SIZE];

    // Obtain the secret key
    tox_self_get_secret_key(self->tox, secret_key);

    // Put the key in a python bytes object
    return PyBytes_FromStringAndSize(secret_key, TOX_SECRET_KEY_SIZE);
}

/* Set the self name to show to our friends. */
static PyObject *
Tox_self_set_name(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"name", NULL};
    const uint8_t *name;
    size_t length;
    Tox_Err_Set_Info tox_err_set_info;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "s#", kwlist, &name, &length))
    {
        return NULL;
    }

    // Set the new name
    if (!tox_self_set_name(self->tox, name, length, &tox_err_set_info)) {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_set_info_strings[tox_err_set_info]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Get the nickname set by tox_self_set_name. */
static PyObject *
Tox_self_get_name(ToxObject *self)
{
    size_t length = tox_self_get_name_size(self->tox);
    uint8_t *name = malloc(length);
    PyObject *s;

    if (!name)
        return PyErr_NoMemory();

    // Obtain the name
    tox_self_get_name(self->tox, name);

    // Put the name in a python string object
    s = PyUnicode_FromStringAndSize(name, length);
    free(name);
    return s;
}

/* Get the status message set by tox_self_set_status_message. */
static PyObject *
Tox_self_get_status_message(ToxObject *self)
{
    size_t length = tox_self_get_status_message_size(self->tox);
    uint8_t *status_message = malloc(length);
    PyObject *s;

    if (!status_message)
        return PyErr_NoMemory();

    // Obtain the status message
    tox_self_get_status_message(self->tox, status_message);

    // Put the status message in a python string object
    s = PyUnicode_FromStringAndSize(status_message, length);
    return s;
}

/* Set the self status message to show to our friends. */
static PyObject *
Tox_self_set_status_message(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"status_message", NULL};
    const uint8_t *status_message;
    size_t length;
    Tox_Err_Set_Info tox_err_set_info;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "s#", kwlist, &status_message, &length))
    {
        return NULL;
    }

    // Set the new name
    if (!tox_self_set_status_message(
        self->tox, status_message, length, &tox_err_set_info))
    {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_set_info_strings[tox_err_set_info]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Set the client's usser status */
static PyObject *
Tox_self_set_status(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"status", NULL};
    Tox_User_Status status;

    // Parse the input arguments (status)
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &status))
        return NULL;

    // Check the status value
    if (status < TOX_USER_STATUS_NONE || status > TOX_USER_STATUS_BUSY) {
        PyErr_SetString(PyExc_ValueError,  "wrong value for status");
        return NULL;
    }

    // Set the status
    tox_self_set_status(self->tox, status);
    Py_RETURN_NONE;
}

/* Returns the client's user status. */
static PyObject *
Tox_self_get_status(ToxObject *self)
{
    return PyLong_FromLong(tox_self_get_status(self->tox));
}

/* Add a friend to the friend list and send a friend request */
static PyObject *
Tox_friend_add(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"address", "message", NULL};
    const uint8_t *address;
    size_t address_length;
    const uint8_t *message;
    size_t length;
    Tox_Err_Friend_Add tox_err_friend_add;
    uint32_t friend_number;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "y#s#", kwlist, &address,
        &address_length, &message, &length))
    {
        return NULL;
    }

    // Check that the address has the valid length
    if (address_length != TOX_ADDRESS_SIZE) {
        PyErr_SetString(PyExc_ValueError, "address wrong length");
        return NULL;
    }

    // Add friend
    friend_number = tox_friend_add(
        self->tox, address, message, length, &tox_err_friend_add);
    if (tox_err_friend_add != TOX_ERR_FRIEND_ADD_OK) {
        // Error, raise a Tox exception
        PyErr_SetString(
            ToxError, tox_err_friend_add_strings[tox_err_friend_add]);
        return NULL;
    }
    return PyLong_FromLong(friend_number);
}

/* Add a friend to the list. Don't send a friend request.
   This function is used when a friend request is received.
   */
static PyObject *
Tox_friend_add_norequest(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"public_key", NULL};
    const char *public_key;
    size_t public_key_size;
    Tox_Err_Friend_Add tox_err_friend_add;
    uint32_t friend_number;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "y#", kwlist, &public_key, &public_key_size))
    {
        return NULL;
    }

    // Check that the key has the valid length
    if (public_key_size != TOX_PUBLIC_KEY_SIZE) {
        PyErr_SetString(PyExc_ValueError, "public key wrong length");
        return NULL;
    }

    // Add friend
    friend_number = tox_friend_add_norequest(
        self->tox, public_key, &tox_err_friend_add);
    if (tox_err_friend_add != TOX_ERR_FRIEND_ADD_OK) {
        // Error, raise a Tox exception
        PyErr_SetString(
            ToxError, tox_err_friend_add_strings[tox_err_friend_add]);
        return NULL;
    }
    return PyLong_FromLong(friend_number);
}

/* Remove a friend from the friend list. */
static PyObject *
Tox_friend_delete(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", NULL};
    uint32_t friend_number;
    Tox_Err_Friend_Delete tox_err_friend_delete;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &friend_number))
        return NULL;

    // Delete the friend
    if (!tox_friend_delete(self->tox, friend_number, &tox_err_friend_delete)) {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError,
            tox_err_friend_delete_strings[tox_err_friend_delete]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Return the friend number associated with that Public Key. */
static PyObject *
Tox_friend_by_public_key(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"public_key", NULL};
    const char *public_key;
    size_t public_key_size;
    Tox_Err_Friend_By_Public_Key error;
    uint32_t friend_number;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "y#", kwlist, &public_key, &public_key_size))
    {
        return NULL;
    }

    // Check that the key has the valid length
    if (public_key_size != TOX_PUBLIC_KEY_SIZE) {
        PyErr_SetString(PyExc_ValueError, "public key wrong length");
        return NULL;
    }

    // Get the friend
    friend_number = tox_friend_by_public_key(self->tox, public_key, &error);
    if (error != TOX_ERR_FRIEND_BY_PUBLIC_KEY_OK) {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_friend_by_public_key_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(friend_number);
}

/* Checks if a friend with the given friend number exists and returns true if
   it does. */
static PyObject *
Tox_friend_exists(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", NULL};
    uint32_t friend_number;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &friend_number))
        return NULL;

    return PyBool_FromLong(tox_friend_exists(self->tox, friend_number));
}

/* Return the list of friend numbers. */
static PyObject *
Tox_self_get_friend_list(ToxObject *self)
{
    size_t length = tox_self_get_friend_list_size(self->tox);

    // Allocate an array for the friends list
    uint32_t *ilist = malloc(length * sizeof(uint32_t));
    if (!ilist)
        return PyErr_NoMemory();

    // Obtain the friend's list
    tox_self_get_friend_list(self->tox, ilist);

    // Build an empty python's list
    PyObject *friend_list = PyList_New(length);
    if (!friend_list)
        goto errpylist;

    // Fill the list of friends
    for (int i = 0; i < length; i++) {
        PyObject *f = PyLong_FromLong(ilist[i]);
        if (!f)
            goto errelem;
        PyList_SET_ITEM(friend_list, i, f);
    }
    free(ilist);
    return friend_list;

errelem:
    Py_DECREF(friend_list);
errpylist:
    free(ilist);
    return NULL;
}

/* Get the Public Key associated with a given friend number. */
static PyObject *
Tox_friend_get_public_key(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", NULL};
    uint32_t friend_number;
    Tox_Err_Friend_Get_Public_Key error;
    uint8_t public_key[TOX_PUBLIC_KEY_SIZE];

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &friend_number))
        return NULL;

    // Obtain the public key
    if (!tox_friend_get_public_key(self->tox, friend_number, public_key,
        &error))
    {
        // Error, raise a Tox exception
        PyErr_SetString(
            ToxError, tox_err_friend_get_public_key_strings[error]);
        return NULL;
    }

    // Return the public key
    return PyBytes_FromStringAndSize(public_key, TOX_PUBLIC_KEY_SIZE);
}

/* Return a unix-time timestamp of the last time the friend associated with a
   given friend number was seen online. */
static PyObject *
Tox_friend_get_last_online(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", NULL};
    uint32_t friend_number;
    Tox_Err_Friend_Get_Last_Online error;
    uint64_t timestamp;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &friend_number))
        return NULL;

    // Obtain the last online timestamp
    timestamp = tox_friend_get_last_online(self->tox, friend_number, &error);
    if (timestamp == UINT64_MAX) {
        // Error, raise a Tox exception
        PyErr_SetString(
            ToxError, tox_err_friend_get_last_online_strings[error]);
        return NULL;
    }

    // Return the timestamp
    return PyLong_FromLong(timestamp);
}

/* Return the name of the friend designated by the given friend number. */
static PyObject *
Tox_friend_get_name(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", NULL};
    uint32_t friend_number;
    Tox_Err_Friend_Query error;
    size_t length;
    uint8_t *name;
    PyObject *o_name = NULL;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &friend_number))
        return NULL;

    // Obtain the name's length
    length = tox_friend_get_name_size(self->tox, friend_number, &error);
    if (error) {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_friend_query_strings[error]);
        return NULL;
    }

    // Allocate an array for the name
    name = malloc(length);
    if (!name)
        return PyErr_NoMemory();

    // Obtain the name
    if (!tox_friend_get_name(self->tox, friend_number, name, &error)) {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_friend_query_strings[error]);
    } else {
        o_name = PyUnicode_FromStringAndSize(name, length);
    }
    free(name);
    return o_name;
}

/* Set the callback for the 'friend_name' event. Pass NONE to unset. */
static PyObject *
Tox_callback_friend_name(ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->friend_name_cb);
    if (cb == Py_None) {
        self->friend_name_cb = NULL;
        tox_callback_friend_name(self->tox, NULL);
    } else {
        self->friend_name_cb = cb;
        tox_callback_friend_name(self->tox, Tox_friend_name_callback);
    }
    Py_RETURN_NONE;
}

/* Return the status message of the friend designated by the given friend
   number. */
static PyObject *
Tox_friend_get_status_message(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", NULL};
    uint32_t friend_number;
    Tox_Err_Friend_Query error;
    size_t length;
    uint8_t *status_message;
    PyObject *o_status_message = NULL;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &friend_number))
        return NULL;

    // Obtain the status message's length
    length = tox_friend_get_status_message_size(
        self->tox, friend_number, &error);
    if (error) {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_friend_query_strings[error]);
        return NULL;
    }

    // Allocate an array for the status message
    status_message = malloc(length);
    if (!status_message)
        return PyErr_NoMemory();

    // Obtain the status message
    if (!tox_friend_get_status_message(
        self->tox, friend_number, status_message, &error))
    {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_friend_query_strings[error]);
    } else {
        o_status_message = PyUnicode_FromStringAndSize(status_message, length);
    }
    free(status_message);
    return o_status_message;
}

/* Set the callback for the 'friend_status_message' event. Pass NONE to unset.
   */
static PyObject *
Tox_callback_friend_status_message(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->friend_status_message_cb);
    if (cb == Py_None) {
        self->friend_status_message_cb = NULL;
        tox_callback_friend_status_message(self->tox, NULL);
    } else {
        self->friend_status_message_cb = cb;
        tox_callback_friend_status_message(
            self->tox, Tox_friend_status_message_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'friend_status' event. Pass NONE to unset.
   */
static PyObject *
Tox_callback_friend_status(ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->friend_status_cb);
    if (cb == Py_None) {
        self->friend_status_cb = NULL;
        tox_callback_friend_status(self->tox, NULL);
    } else {
        self->friend_status_cb = cb;
        tox_callback_friend_status(self->tox, Tox_friend_status_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'friend_connection_status' event.
   Pass NONE to unset.
   */
static PyObject *
Tox_callback_friend_connection_status(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->friend_connection_status_cb);
    if (cb == Py_None) {
        self->friend_connection_status_cb = NULL;
        tox_callback_friend_connection_status(self->tox, NULL);
    } else {
        self->friend_connection_status_cb = cb;
        tox_callback_friend_connection_status(
            self->tox, Tox_friend_connection_status_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'friend_typing' event. Pass NONE to unset.
   */
static PyObject *
Tox_callback_friend_typing(ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->friend_typing_cb);
    if (cb == Py_None) {
        self->friend_typing_cb = NULL;
        tox_callback_friend_typing(self->tox, NULL);
    } else {
        self->friend_typing_cb = cb;
        tox_callback_friend_typing(self->tox, Tox_friend_typing_callback);
    }
    Py_RETURN_NONE;
}

/* Set the client's typing status for a friend.
   The client is responsible for turning it on or off. */
static PyObject *
Tox_self_set_typing(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", "typing", NULL};
    uint32_t friend_number;
    bool typing;
    Tox_Err_Set_Typing error;

    // Parse the input arguments (status)
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "Ip", kwlist, &friend_number, &typing))
    {
        return NULL;
    }

    // Set the typing status
    if (!tox_self_set_typing(self->tox, friend_number, typing, &error)) {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_set_typing_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Send a message to a friend. */
static PyObject *
Tox_friend_send_message(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", "type", "message", NULL};
    uint32_t friend_number;
    Tox_Message_Type type;
    const uint8_t *message;
    size_t length;
    Tox_Err_Friend_Send_Message tox_err_friend_send_message;
    uint32_t message_id;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "Iis#", kwlist, &friend_number, &type, &message, &length))
    {
        return NULL;
    }

    // Send the message
    message_id = tox_friend_send_message(self->tox, friend_number, type,
        message, length, &tox_err_friend_send_message);
    if (tox_err_friend_send_message != TOX_ERR_FRIEND_SEND_MESSAGE_OK) {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError,
            tox_err_friend_send_message_strings[tox_err_friend_send_message]);
        return NULL;
    }
    return PyLong_FromLong(message_id);
}

/* Set the callback for the 'friend_read_receipt' event. Pass NONE to unset. */
static PyObject *
Tox_callback_friend_read_receipt(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->friend_read_receipt_cb);
    if (cb == Py_None) {
        self->friend_read_receipt_cb = NULL;
        tox_callback_friend_read_receipt(self->tox, NULL);
    } else {
        self->friend_read_receipt_cb = cb;
        tox_callback_friend_read_receipt(
            self->tox, Tox_friend_read_receipt_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback triggered by the reception of friend requests */
static PyObject *
Tox_callback_friend_request(ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->friend_request_cb);
    if (cb == Py_None) {
        self->friend_request_cb = NULL;
        tox_callback_friend_request(self->tox, NULL);
    } else {
        self->friend_request_cb = cb;
        tox_callback_friend_request(self->tox, Tox_friend_request_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback triggered by the reception of friend messages */
static PyObject *
Tox_callback_friend_message(ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->friend_message_cb);
    if (cb == Py_None) {
        self->friend_message_cb = NULL;
        tox_callback_friend_message(self->tox, NULL);
    } else {
        self->friend_message_cb = cb;
        tox_callback_friend_message(self->tox, Tox_friend_message_callback);
    }
    Py_RETURN_NONE;
}

/* Send a file control command to a friend for a given file transfer. */
static PyObject *
Tox_file_control(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", "file_number", "control", NULL};
    uint32_t friend_number;
    uint32_t file_number;
    Tox_File_Control control;
    Tox_Err_File_Control error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "IIi", kwlist, &friend_number, &file_number, &control))
    {
        return NULL;
    }

    // Send the file control
    if (!tox_file_control(self->tox, friend_number, file_number, control,
        &error))
    {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_file_control_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'file_recv_control' event. Pass None to unset. */
static PyObject *
Tox_callback_file_recv_control(ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->file_recv_control_cb);
    if (cb == Py_None) {
        self->file_recv_control_cb = NULL;
        tox_callback_file_recv_control(self->tox, NULL);
    } else {
        self->file_recv_control_cb = cb;
        tox_callback_file_recv_control(
            self->tox, Tox_file_recv_control_callback);
    }
    Py_RETURN_NONE;
}

/* Sends a file file seek control command to a friend for a given file
   transfer. */
static PyObject *
Tox_file_seek(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", "file_number", "position", NULL};
    uint32_t friend_number;
    uint32_t file_number;
    uint64_t position;
    Tox_Err_File_Seek error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "IIL", kwlist, &friend_number, &file_number, &position))
    {
        return NULL;
    }

    // Send the file seek control
    tox_file_seek(self->tox, friend_number, file_number, position, &error);
    if (error)
    {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_file_seek_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Get the file id associated to the file transfer. */
static PyObject *
Tox_file_get_file_id(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", "file_number", NULL};
    uint32_t friend_number;
    uint32_t file_number;
    uint8_t file_id[TOX_FILE_ID_LENGTH];
    Tox_Err_File_Get error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "II", kwlist, &friend_number, &file_number))
    {
        return NULL;
    }

    // Get the file id
    if (!tox_file_get_file_id(
        self->tox, friend_number, file_number, file_id, &error))
    {
        // Error, raise a Tox exception
        PyErr_SetString(ToxError, tox_err_file_get_strings[error]);
        return NULL;
    }
    return PyUnicode_FromString(file_id);
}

/* Send a file transmission request. */
static PyObject *
Tox_file_send(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", "kind", "file_size", "file_id",
        "filename", NULL};
    uint32_t friend_number;
    uint32_t kind;
    uint64_t file_size;
    uint8_t *file_id;
    size_t file_id_length;
    uint8_t *filename;
    size_t filename_length;
    Tox_Err_File_Send error;
    uint32_t file_number;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "IILs#s#", kwlist,
        &friend_number, &kind, &file_size, &file_id, &file_id_length,
        &filename, &filename_length))
    {
        return NULL;
    }

    // Check the parameters
    if (kind < TOX_FILE_KIND_DATA || kind > TOX_FILE_KIND_AVATAR) {
        PyErr_SetString(ToxError, "wrong kind");
        return NULL;
    }
    if (file_id_length != TOX_FILE_ID_LENGTH) {
        PyErr_SetString(ToxError, "file_id of wrong length");
    }

    // Execute the operation
    file_number = tox_file_send(self->tox, friend_number, kind, file_size,
        file_id, filename, filename_length, &error);
    if (error) {
        PyErr_SetString(ToxError, tox_err_file_send_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(file_number);
}

/* Send a chunk of file data to a friend. */
static PyObject *
Tox_file_send_chunk(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {
        "friend_number", "file_number", "position", "data", NULL};
    uint32_t friend_number;
    uint32_t file_number;
    uint64_t position;
    uint8_t *data;
    size_t length;
    Tox_Err_File_Send_Chunk error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "IILy#", kwlist,
        &friend_number, &file_number, &position, &data, &length))
    {
        return NULL;
    }

    // Execute the operation
    if (!tox_file_send_chunk(self->tox, friend_number, file_number, position,
        data, length, &error))
    {
        PyErr_SetString(ToxError, tox_err_file_send_chunk_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'file_chunk_request' event. Pass None to unset. */
static PyObject *
Tox_callback_file_chunk_request(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->file_chunk_request_cb);
    if (cb == Py_None) {
        self->file_chunk_request_cb = NULL;
        tox_callback_file_chunk_request(self->tox, NULL);
    } else {
        self->file_chunk_request_cb = cb;
        tox_callback_file_chunk_request(
            self->tox, Tox_file_chunk_request_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'file_recv' event. Pass None to unset. */
static PyObject *
Tox_callback_file_recv(ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->file_recv_cb);
    if (cb == Py_None) {
        self->file_recv_cb = NULL;
        tox_callback_file_recv(self->tox, NULL);
    } else {
        self->file_recv_cb = cb;
        tox_callback_file_recv(self->tox, Tox_file_recv_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'file_recv_chunk' event. Pass None to unset. */
static PyObject *
Tox_callback_file_recv_chunk(ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->file_recv_chunk_cb);
    if (cb == Py_None) {
        self->file_recv_chunk_cb = NULL;
        tox_callback_file_recv_chunk(self->tox, NULL);
    } else {
        self->file_recv_chunk_cb = cb;
        tox_callback_file_recv_chunk(self->tox, Tox_file_recv_chunk_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'conference_invite' event. Pass None to unset. */
static PyObject *
Tox_callback_conference_invite(ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->conference_invite_cb);
    if (cb == Py_None) {
        self->conference_invite_cb = NULL;
        tox_callback_conference_invite(self->tox, NULL);
    } else {
        self->conference_invite_cb = cb;
        tox_callback_conference_invite(
            self->tox, Tox_conference_invite_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'conference_connected' event. Pass None to unset.
   */
static PyObject *
Tox_callback_conference_connected(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->conference_connected_cb);
    if (cb == Py_None) {
        self->conference_connected_cb = NULL;
        tox_callback_conference_connected(self->tox, NULL);
    } else {
        self->conference_connected_cb = cb;
        tox_callback_conference_connected(
            self->tox, Tox_conference_connected_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'conference_message' event. Pass None to unset.
   */
static PyObject *
Tox_callback_conference_message(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->conference_message_cb);
    if (cb == Py_None) {
        self->conference_message_cb = NULL;
        tox_callback_conference_message(self->tox, NULL);
    } else {
        self->conference_message_cb = cb;
        tox_callback_conference_message(
            self->tox, Tox_conference_message_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'conference_title' event. Pass None to unset. */
static PyObject *
Tox_callback_conference_title(ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->conference_title_cb);
    if (cb == Py_None) {
        self->conference_title_cb = NULL;
        tox_callback_conference_title(self->tox, NULL);
    } else {
        self->conference_title_cb = cb;
        tox_callback_conference_title(
            self->tox, Tox_conference_title_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'conference_peer_name' event. Pass None to unset.
   */
static PyObject *
Tox_callback_conference_peer_name(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->conference_peer_name_cb);
    if (cb == Py_None) {
        self->conference_peer_name_cb = NULL;
        tox_callback_conference_peer_name(self->tox, NULL);
    } else {
        self->conference_peer_name_cb = cb;
        tox_callback_conference_peer_name(
            self->tox, Tox_conference_peer_name_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'conference_peer_list_changed' event.
   Pass None to unset.
   */
static PyObject *
Tox_callback_conference_peer_list_changed(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->conference_peer_list_changed_cb);
    if (cb == Py_None) {
        self->conference_peer_list_changed_cb = NULL;
        tox_callback_conference_peer_list_changed(self->tox, NULL);
    } else {
        self->conference_peer_list_changed_cb = cb;
        tox_callback_conference_peer_list_changed(
            self->tox, Tox_conference_peer_list_changed_callback);
    }
    Py_RETURN_NONE;
}

/* Creates a new conference. */
static PyObject *
Tox_conference_new(ToxObject *self)
{
    uint32_t conference_number;
    Tox_Err_Conference_New error;

    // Create the conference
    conference_number = tox_conference_new(self->tox, &error);
    if (error) {
        PyErr_SetString(ToxError, tox_err_conference_new_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(conference_number);
}

/* This function deletes a conference. */
static PyObject *
Tox_conference_delete(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number"};
    uint32_t conference_number;
    Tox_Err_Conference_Delete error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "I", kwlist, &conference_number))
    {
        return NULL;
    }

    // Delete the conference
    if (!tox_conference_delete(self->tox, conference_number, &error)) {
        PyErr_SetString(ToxError, tox_err_conference_delete_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Return the number of peers in the conference.
   Return value is unspecified on failure.
   */
static PyObject *
Tox_conference_peer_count(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number"};
    uint32_t conference_number;
    Tox_Err_Conference_Peer_Query error;
    uint32_t count;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "I", kwlist, &conference_number))
    {
        return NULL;
    }

    // Get the peer count
    count = tox_conference_peer_count(self->tox, conference_number, &error);
    if (error) {
        PyErr_SetString(
            ToxError, tox_err_conference_peer_query_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(count);
}

/* Return the name of peer_number who is in conference_number. */
static PyObject *
Tox_conference_peer_get_name(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number", "peer_number"};
    uint32_t conference_number;
    uint32_t peer_number;
    Tox_Err_Conference_Peer_Query error;
    size_t length;
    uint8_t *name;
    PyObject *o_name = NULL;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "II", kwlist, &conference_number, &peer_number))
    {
        return NULL;
    }

    // Get the peer name
    length = tox_conference_peer_get_name_size(
        self->tox, conference_number, peer_number, &error);
    if (error) {
        PyErr_SetString(
            ToxError, tox_err_conference_peer_query_strings[error]);
        return NULL;
    }
    name = malloc(length);
    if (!name)
        return PyErr_NoMemory();
    if (!tox_conference_peer_get_name(
        self->tox, conference_number, peer_number, name, &error))
    {
        PyErr_SetString(
            ToxError, tox_err_conference_peer_query_strings[error]);
    } else {
        o_name = PyUnicode_FromStringAndSize(name, length);
    }
    free(name);
    return o_name;
}

/* Return the public key of peer_number who is in conference_number. */
static PyObject *
Tox_conference_peer_get_public_key(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number", "peer_number"};
    uint32_t conference_number;
    uint32_t peer_number;
    Tox_Err_Conference_Peer_Query error;
    uint8_t public_key[TOX_PUBLIC_KEY_SIZE];

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "II", kwlist, &conference_number, &peer_number))
    {
        return NULL;
    }

    // Get the peer public key
    if (!tox_conference_peer_get_public_key(
        self->tox, conference_number, peer_number, public_key, &error))
    {
        PyErr_SetString(
            ToxError, tox_err_conference_peer_query_strings[error]);
        return NULL;
    }
    return PyBytes_FromStringAndSize(public_key, TOX_PUBLIC_KEY_SIZE);
}

/* Return true if passed peer_number corresponds to our own. */
static PyObject *
Tox_conference_peer_number_is_ours(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number", "peer_number"};
    uint32_t conference_number;
    uint32_t peer_number;
    Tox_Err_Conference_Peer_Query error;
    bool is_ours;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "II", kwlist, &conference_number, &peer_number))
    {
        return NULL;
    }

    // Get the result
    is_ours = tox_conference_peer_number_is_ours(
        self->tox, conference_number, peer_number, &error);
    if (error) {
        PyErr_SetString(
            ToxError, tox_err_conference_peer_query_strings[error]);
        return NULL;
    }
    return PyBool_FromLong(is_ours);
}

/* Return the number of offline peers in the conference. */
static PyObject *
Tox_conference_offline_peer_count(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number"};
    uint32_t conference_number;
    Tox_Err_Conference_Peer_Query error;
    uint32_t number;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "I", kwlist, &conference_number))
    {
        return NULL;
    }

    // Get the result
    number = tox_conference_offline_peer_count(
        self->tox, conference_number, &error);
    if (error) {
        PyErr_SetString(
            ToxError, tox_err_conference_peer_query_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(number);
}

/* Return the name of offline_peer_number who is in conference_number. */
static PyObject *
Tox_conference_offline_peer_get_name(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number", "offline_peer_number"};
    uint32_t conference_number;
    uint32_t offline_peer_number;
    Tox_Err_Conference_Peer_Query error;
    size_t length;
    uint8_t *name;
    PyObject *o_name = NULL;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "II", kwlist, &conference_number, &offline_peer_number))
    {
        return NULL;
    }

    // Get the peer name
    length = tox_conference_offline_peer_get_name_size(
        self->tox, conference_number, offline_peer_number, &error);
    if (error) {
        PyErr_SetString(
            ToxError, tox_err_conference_peer_query_strings[error]);
        return NULL;
    }
    name = malloc(length);
    if (!name)
        return PyErr_NoMemory();
    if (!tox_conference_offline_peer_get_name(
        self->tox, conference_number, offline_peer_number, name, &error))
    {
        PyErr_SetString(
            ToxError, tox_err_conference_peer_query_strings[error]);
    } else {
        o_name = PyUnicode_FromStringAndSize(name, length);
    }
    free(name);
    return o_name;
}

/* Return the public key of offline_peer_number who is in conference_number. */
static PyObject *
Tox_conference_offline_peer_get_public_key(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number", "offline_peer_number"};
    uint32_t conference_number;
    uint32_t offline_peer_number;
    Tox_Err_Conference_Peer_Query error;
    uint8_t public_key[TOX_PUBLIC_KEY_SIZE];

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "II", kwlist, &conference_number, &offline_peer_number))
    {
        return NULL;
    }

    // Get the peer public key
    if (!tox_conference_offline_peer_get_public_key(
        self->tox, conference_number, offline_peer_number, public_key, &error))
    {
        PyErr_SetString(
            ToxError, tox_err_conference_peer_query_strings[error]);
        return NULL;
    }
    return PyBytes_FromStringAndSize(public_key, TOX_PUBLIC_KEY_SIZE);
}

/* Return a unix-time timestamp of the last time offline_peer_number was seen
   to be active. */
static PyObject *
Tox_conference_offline_peer_get_last_active(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number", "offline_peer_number"};
    uint32_t conference_number;
    uint32_t offline_peer_number;
    Tox_Err_Conference_Peer_Query error;
    uint64_t timestamp;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "II", kwlist, &conference_number, &offline_peer_number))
    {
        return NULL;
    }

    // Return the timestamp
    timestamp = tox_conference_offline_peer_get_last_active(
        self->tox, conference_number, offline_peer_number, &error);
    if (error) {
        PyErr_SetString(
            ToxError, tox_err_conference_peer_query_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(timestamp);
}

/* Set maximum number of offline peers to store, overriding the default. */
static PyObject *
Tox_conference_set_max_offline(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number", "max_offline_peers"};
    uint32_t conference_number;
    uint32_t max_offline_peers;
    Tox_Err_Conference_Set_Max_Offline error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "II", kwlist, &conference_number, &max_offline_peers))
    {
        return NULL;
    }

    // Set the number of offline peers
    tox_conference_set_max_offline(
        self->tox, conference_number, max_offline_peers, &error);
    if (error) {
        PyErr_SetString(
            ToxError, tox_err_conference_set_max_offline_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Invites a friend to a conference. */
static PyObject *
Tox_conference_invite(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", "conference_number"};
    uint32_t friend_number;
    uint32_t conference_number;
    Tox_Err_Conference_Invite error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "II", kwlist, &friend_number, &conference_number))
    {
        return NULL;
    }

    // Send the invitation
    if (!tox_conference_invite(
        self->tox, friend_number, conference_number, &error))
    {
        PyErr_SetString(
            ToxError, tox_err_conference_invite_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Joins a conference that the client has been invited to. */
static PyObject *
Tox_conference_join(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", "cookie"};
    uint32_t friend_number;
    uint8_t *cookie;
    size_t length;
    Tox_Err_Conference_Join error;
    uint32_t conference_number;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "Iy#", kwlist, &friend_number, &cookie, &length))
    {
        return NULL;
    }

    conference_number = tox_conference_join(
        self->tox, friend_number, cookie, length, &error);
    if (error) {
        PyErr_SetString(
            ToxError, tox_err_conference_join_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(conference_number);
}

/* Send a text chat message to the conference. */
static PyObject *
Tox_conference_send_message(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number", "type", "message"};
    uint32_t conference_number;
    Tox_Message_Type type;
    uint8_t *message;
    size_t length;
    Tox_Err_Conference_Send_Message error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "Iis#", kwlist,
        &conference_number, &type, &message, &length))
    {
        return NULL;
    }

    if (!tox_conference_send_message(
        self->tox, conference_number, type, message, length, &error))
    {
        PyErr_SetString(
            ToxError, tox_err_conference_send_message_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Return the title designated by the given conference number. */
static PyObject *
Tox_conference_get_title(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number"};
    uint32_t conference_number;
    Tox_Err_Conference_Title error;
    size_t length;
    uint8_t *title;
    PyObject *o_title = NULL;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "I", kwlist, &conference_number))
    {
        return NULL;
    }

    // Get the conference title
    length = tox_conference_get_title_size(
        self->tox, conference_number, &error);
    if (error) {
        PyErr_SetString(ToxError, tox_err_conference_title_strings[error]);
        return NULL;
    }
    title = malloc(length);
    if (!title)
        return PyErr_NoMemory();
    if (!tox_conference_get_title(self->tox, conference_number, title, &error))
    {
        PyErr_SetString(ToxError, tox_err_conference_title_strings[error]);
    } else {
        o_title = PyUnicode_FromStringAndSize(title, length);
    }
    free(title);
    return o_title;
}

/* Set the conference title and broadcast it to the rest of the conference. */
static PyObject *
Tox_conference_set_title(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number", "title"};
    uint32_t conference_number;
    uint8_t *title;
    size_t length;
    Tox_Err_Conference_Title error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "Is#", kwlist,
        &conference_number, &title, &length))
    {
        return NULL;
    }

    if (!tox_conference_set_title(
        self->tox, conference_number, title, length, &error))
    {
        PyErr_SetString(ToxError, tox_err_conference_title_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Return the list of valid conference IDs. */
static PyObject *
Tox_conference_get_chatlist(ToxObject *self)
{
    size_t length = tox_conference_get_chatlist_size(self->tox);

    // Allocate an array for the chatlist
    uint32_t *chatlist = malloc(length * sizeof(uint32_t));
    if (!chatlist)
        return PyErr_NoMemory();

    // Obtain the friend's list
    tox_conference_get_chatlist(self->tox, chatlist);

    // Build an empty python's list
    PyObject *o_chatlist = PyList_New(length);
    if (!o_chatlist)
        goto errpylist;

    // Fill the list of friends
    for (int i = 0; i < length; i++) {
        PyObject *c = PyLong_FromLong(chatlist[i]);
        if (!c)
            goto errelem;
        PyList_SET_ITEM(o_chatlist, i, c);
    }
    free(chatlist);
    return o_chatlist;

errelem:
    Py_DECREF(o_chatlist);
errpylist:
    free(chatlist);
    return NULL;
}

/* Returns the type of conference that conference_number is. */
static PyObject *
Tox_conference_get_type(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number"};
    uint32_t conference_number;
    Tox_Err_Conference_Get_Type error;
    Tox_Conference_Type type;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "I", kwlist, &conference_number))
    {
        return NULL;
    }

    type = tox_conference_get_type(self->tox, conference_number, &error);
    if (error) {
        PyErr_SetString(
            ToxError, tox_err_conference_get_type_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(type);
}

/* Get the conference unique ID. */
static PyObject *
Tox_conference_get_id(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"conference_number"};
    uint32_t conference_number;
    uint8_t id[TOX_CONFERENCE_ID_SIZE];

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "I", kwlist, &conference_number))
    {
        return NULL;
    }

    tox_conference_get_id(self->tox, conference_number, id);
    return PyBytes_FromStringAndSize(id, TOX_CONFERENCE_ID_SIZE);
}

/* Return the conference number associated with the specified id. */
static PyObject *
Tox_conference_by_id(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"id"};
    uint8_t *id;
    size_t length;
    Tox_Err_Conference_By_Id error;
    uint32_t conference_number;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &id, &length))
        return NULL;
    if (length != TOX_CONFERENCE_ID_SIZE) {
        PyErr_SetString(PyExc_ValueError,  "wrong id size");
        return NULL;
    }

    conference_number = tox_conference_by_id(self->tox, id, &error);
    if (error) {
        PyErr_SetString(ToxError, tox_err_conference_by_id_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(conference_number);
}

/* Send a custom lossy packet to a friend. */
static PyObject *
Tox_friend_send_lossy_packet(ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", "data"};
    uint32_t friend_number;
    uint8_t *data;
    size_t length;
    Tox_Err_Friend_Custom_Packet error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "Iy#", kwlist, &friend_number, &data, &length))
    {
        return NULL;
    }

    if (!tox_friend_send_lossy_packet(
        self->tox, friend_number, data, length, &error))
    {
        PyErr_SetString(ToxError, tox_err_friend_custom_packet_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Send a custom lossless packet to a friend. */
static PyObject *
Tox_friend_send_lossless_packet(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"friend_number", "data"};
    uint32_t friend_number;
    uint8_t *data;
    size_t length;
    Tox_Err_Friend_Custom_Packet error;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "Iy#", kwlist, &friend_number, &data, &length))
    {
        return NULL;
    }

    if (!tox_friend_send_lossless_packet(
        self->tox, friend_number, data, length, &error))
    {
        PyErr_SetString(ToxError, tox_err_friend_custom_packet_strings[error]);
        return NULL;
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'friend_lossy_packet' event. Pass None to unset. */
static PyObject *
Tox_callback_friend_lossy_packet(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->friend_lossy_packet_cb);
    if (cb == Py_None) {
        self->friend_lossy_packet_cb = NULL;
        tox_callback_friend_lossy_packet(self->tox, NULL);
    } else {
        self->friend_lossy_packet_cb = cb;
        tox_callback_friend_lossy_packet(
            self->tox, Tox_friend_lossy_packet_callback);
    }
    Py_RETURN_NONE;
}

/* Set the callback for the 'friend_lossless_packet' event.
   Pass None to unset. */
static PyObject *
Tox_callback_friend_lossless_packet(
    ToxObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *cb;

    // Get the callback object
    if (!(cb = get_callback(args, kwds)))
        return NULL;

    // Set the callback
    Py_XDECREF(self->friend_lossless_packet_cb);
    if (cb == Py_None) {
        self->friend_lossless_packet_cb = NULL;
        tox_callback_friend_lossless_packet(self->tox, NULL);
    } else {
        self->friend_lossless_packet_cb = cb;
        tox_callback_friend_lossless_packet(
            self->tox, Tox_friend_lossless_packet_callback);
    }
    Py_RETURN_NONE;
}

/* Get the temporary DHT public key of this instance. */
static PyObject *
Tox_self_get_dht_id(ToxObject *self)
{
    uint8_t dht_id[TOX_PUBLIC_KEY_SIZE];

    tox_self_get_dht_id(self->tox, dht_id);
    return PyBytes_FromStringAndSize(dht_id, TOX_PUBLIC_KEY_SIZE);
}

/* Return the UDP port this Tox instance is bound to. */
static PyObject *
Tox_self_get_udp_port(ToxObject *self)
{
    Tox_Err_Get_Port error;
    uint16_t port = tox_self_get_udp_port(self->tox, &error);

    if (error) {
        PyErr_SetString(ToxError, tox_err_get_port_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(port);
}

/* Return the TCP port this Tox instance is bound to. */
static PyObject *
Tox_self_get_tcp_port(ToxObject *self)
{
    Tox_Err_Get_Port error;
    uint16_t port = tox_self_get_tcp_port(self->tox, &error);

    if (error) {
        PyErr_SetString(ToxError, tox_err_get_port_strings[error]);
        return NULL;
    }
    return PyLong_FromLong(port);
}

/* Definition of Tox methods. */
static PyMethodDef Tox_methods[] = {
    {"bootstrap", (PyCFunction) Tox_bootstrap, METH_VARARGS | METH_KEYWORDS,
     "Bootstrap to the DHT network"},
    {"add_tcp_relay", (PyCFunction) Tox_add_tcp_relay,
     METH_VARARGS | METH_KEYWORDS,
     "Adds additional host:port pair as TCP relay"},
    {"callback_self_connection_status",
     (PyCFunction) Tox_callback_self_connection_status,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback triggered by updates in our connection status"},
    {"get_savedata", (PyCFunction) Tox_get_savedata, METH_NOARGS,
     "Get the dumped data of this Tox instance to be saved"},
    {"iterate", (PyCFunction) Tox_iterate, METH_NOARGS, "Check Tox events"},
    {"iteration_interval", (PyCFunction) Tox_iteration_interval, METH_NOARGS,
     "Return the recommended iteration interval to use for optimal"
     " performance"},
    {"self_get_address", (PyCFunction) Tox_self_get_address, METH_NOARGS,
     "Return the self Tox address"},
    {"self_set_nospam", (PyCFunction) Tox_self_set_nospam,
     METH_VARARGS | METH_KEYWORDS,
     "Set the 4-byte nospam part of the address"},
    {"self_get_nospam", (PyCFunction) Tox_self_get_nospam, METH_NOARGS,
     "Get the 4-byte nospam part of the address"},
    {"self_get_public_key", (PyCFunction) Tox_self_get_public_key, METH_NOARGS,
     "Get the Tox Public Key"},
    {"self_get_secret_key", (PyCFunction) Tox_self_get_secret_key, METH_NOARGS,
     "Get the Tox Secret Key"},
    {"self_set_name", (PyCFunction) Tox_self_set_name,
     METH_VARARGS | METH_KEYWORDS,
     "Set the self name to show to our friends"},
    {"self_get_name", (PyCFunction) Tox_self_get_name, METH_NOARGS,
     "Get the nickname set by tox_self_set_name"},
    {"self_set_status_message", (PyCFunction) Tox_self_set_status_message,
     METH_VARARGS | METH_KEYWORDS,
     "Set the self status message to show to our friends"},
    {"self_get_status_message", (PyCFunction) Tox_self_get_status_message,
     METH_NOARGS, "Get the status message set by tox_self_set_status_message"},
    {"self_set_status", (PyCFunction) Tox_self_set_status,
     METH_VARARGS | METH_KEYWORDS, "Set the client's usser status"},
    {"self_get_status", (PyCFunction) Tox_self_get_status, METH_NOARGS,
     "Returns the client's user status"},
    {"friend_add", (PyCFunction) Tox_friend_add, METH_VARARGS | METH_KEYWORDS,
     "Add a friend to the friend list and send a friend request"},
    {"friend_add_norequest", (PyCFunction) Tox_friend_add_norequest,
     METH_VARARGS | METH_KEYWORDS,
     "Add a friend to the list, but don't send a friend request"},
    {"friend_delete", (PyCFunction) Tox_friend_delete,
     METH_VARARGS | METH_KEYWORDS, "Remove a friend from the friend list"},
    {"friend_by_public_key", (PyCFunction) Tox_friend_by_public_key,
     METH_VARARGS | METH_KEYWORDS,
     "Return the friend number associated with that Public Key"},
    {"friend_exists", (PyCFunction) Tox_friend_exists,
     METH_VARARGS | METH_KEYWORDS,
     "Checks if a friend with the given friend number exists and returns true"
     " if it does"},
    {"self_get_friend_list", (PyCFunction) Tox_self_get_friend_list,
     METH_NOARGS, "Return the list of friend numbers"},
    {"friend_get_public_key", (PyCFunction) Tox_friend_get_public_key,
     METH_VARARGS | METH_KEYWORDS,
     "Get the Public Key associated with a given friend number"},
    {"friend_get_last_online", (PyCFunction) Tox_friend_get_last_online,
     METH_VARARGS | METH_KEYWORDS,
     "Return a unix-time timestamp of the last time the friend associated with"
     " a given friend number was seen online"},
    {"friend_get_name", (PyCFunction) Tox_friend_get_name,
     METH_VARARGS | METH_KEYWORDS,
     "Return the name of the friend designated by the given friend number"},
    {"callback_friend_name", (PyCFunction) Tox_callback_friend_name,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback for the 'friend_name' event. Pass NONE to unset"},
    {"friend_get_status_message", (PyCFunction) Tox_friend_get_status_message,
     METH_VARARGS | METH_KEYWORDS,
     "Return the status message of the friend designated by the given friend"
     " number"},
    {"callback_friend_status_message",
     (PyCFunction) Tox_callback_friend_status_message,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback for the 'friend_status_message' event. Pass NONE to"
     " unset"},
    {"callback_friend_status", (PyCFunction) Tox_callback_friend_status,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback for the 'friend_status' event. Pass NONE to unset"},
    {"callback_friend_connection_status",
     (PyCFunction) Tox_callback_friend_connection_status,
     METH_VARARGS | METH_KEYWORDS, "Set the callback for the "
     "'friend_connection_status' event. Pass NONE to unset"},
    {"callback_friend_typing", (PyCFunction) Tox_callback_friend_typing,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback for the 'friend_typing' event. Pass NONE to unset"},
    {"self_set_typing", (PyCFunction) Tox_self_set_typing,
     METH_VARARGS | METH_KEYWORDS,
     "Set the client's typing status for a friend"},
    {"friend_send_message",
     (PyCFunction) Tox_friend_send_message, METH_VARARGS | METH_KEYWORDS,
     "Send a message to a friend"},
    {"callback_friend_read_receipt",
     (PyCFunction) Tox_callback_friend_read_receipt,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback for the 'friend_read_receipt' event. "
     "Pass NONE to unset"},
    {"callback_friend_request", (PyCFunction) Tox_callback_friend_request,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback triggered by the reception of friend requests"},
    {"callback_friend_message", (PyCFunction) Tox_callback_friend_message,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback triggered by the reception of friend messages"},
    {"file_control", (PyCFunction) Tox_file_control,
     METH_VARARGS | METH_KEYWORDS,
     "Send a file control command to a friend for a given file transfer"},
    {"callback_file_recv_control",
     (PyCFunction) Tox_callback_file_recv_control,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback for the 'file_recv_control' event. Pass None to unset"},
    {"file_seek", (PyCFunction) Tox_file_seek,
     METH_VARARGS | METH_KEYWORDS,
     "Send a file seek control command to a friend for a given file transfer"},
    {"file_get_file_id", (PyCFunction) Tox_file_get_file_id,
     METH_VARARGS | METH_KEYWORDS,
     "Get the file id associated to the file transfer"},
    {"file_send", (PyCFunction) Tox_file_send, METH_VARARGS | METH_KEYWORDS,
     "Send a file transmission request"},
    {"file_send_chunk", (PyCFunction) Tox_file_send_chunk,
     METH_VARARGS | METH_KEYWORDS, "Send a chunk of file data to a friend"},
    {"callback_file_chunk_request",
     (PyCFunction) Tox_callback_file_chunk_request,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback for the 'file_chunk_request' event. "
     "Pass None to unset"},
    {"callback_file_recv", (PyCFunction) Tox_callback_file_recv,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback for the 'file_recv' event. Pass None to unset"},
    {"callback_file_recv_chunk", (PyCFunction) Tox_callback_file_recv_chunk,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback for the 'file_recv_chunk' event. Pass None to unset"},
    {"callback_conference_invite",
     (PyCFunction) Tox_callback_conference_invite,
     METH_VARARGS | METH_KEYWORDS,
     "Set the callback for the 'conference_invite' event. Pass None to unset"},
    {"callback_conference_connected",
     (PyCFunction) Tox_callback_conference_connected,
     METH_VARARGS | METH_KEYWORDS, "Set the callback for the "
     "'conference_connected' event. Pass None to unset"},
    {"callback_conference_message",
     (PyCFunction) Tox_callback_conference_message,
     METH_VARARGS | METH_KEYWORDS, "Set the callback for the "
     "'conference_message' event. Pass None to unset"},
    {"callback_conference_title", (PyCFunction) Tox_callback_conference_title,
     METH_VARARGS | METH_KEYWORDS, "Set the callback for the "
     "'conference_title' event. Pass None to unset"},
    {"callback_conference_peer_name",
     (PyCFunction) Tox_callback_conference_peer_name,
     METH_VARARGS | METH_KEYWORDS, "Set the callback for the "
     "'conference_peer_name' event. Pass None to unset"},
    {"callback_conference_peer_list_changed",
     (PyCFunction) Tox_callback_conference_peer_list_changed,
     METH_VARARGS | METH_KEYWORDS, "Set the callback for the "
     "'conference_peer_list_changed' event. Pass None to unset"},
    {"conference_new", (PyCFunction) Tox_conference_new, METH_NOARGS,
     "Creates a new conference"},
    {"conference_delete", (PyCFunction) Tox_conference_delete,
     METH_VARARGS | METH_KEYWORDS, "This function deletes a conference"},
    {"conference_peer_count", (PyCFunction) Tox_conference_peer_count,
     METH_VARARGS | METH_KEYWORDS,
     "Return the number of peers in the conference"},
    {"conference_peer_get_name", (PyCFunction) Tox_conference_peer_get_name,
     METH_VARARGS | METH_KEYWORDS,
     "Return the name of peer_number who is in conference_number"},
    {"conference_peer_get_public_key",
     (PyCFunction) Tox_conference_peer_get_public_key,
     METH_VARARGS | METH_KEYWORDS,
     "Return the public key of peer_number who is in conference_number"},
    {"conference_peer_number_is_ours",
     (PyCFunction) Tox_conference_peer_number_is_ours,
     METH_VARARGS | METH_KEYWORDS,
     "Return true if passed peer_number corresponds to our own"},
    {"conference_offline_peer_count",
     (PyCFunction) Tox_conference_offline_peer_count,
     METH_VARARGS | METH_KEYWORDS,
     "Return the number of offline peers in the conference"},
    {"conference_offline_peer_get_name",
     (PyCFunction) Tox_conference_offline_peer_get_name,
     METH_VARARGS | METH_KEYWORDS,
     "Return the name of offline_peer_number who is in conference_number"},
    {"conference_offline_peer_get_public_key",
     (PyCFunction) Tox_conference_offline_peer_get_public_key,
     METH_VARARGS | METH_KEYWORDS, "Return the public key of"
     " offline_peer_number who is in conference_number"},
    {"conference_offline_peer_get_last_active",
     (PyCFunction) Tox_conference_offline_peer_get_last_active,
     METH_VARARGS | METH_KEYWORDS, "Return a unix-time timestamp of the last"
     " time offline_peer_number was seen to be active"},
    {"conference_set_max_offline",
     (PyCFunction) Tox_conference_set_max_offline,
     METH_VARARGS | METH_KEYWORDS,
     "Set maximum number of offline peers to store, overriding the default"},
    {"conference_invite", (PyCFunction) Tox_conference_invite,
     METH_VARARGS | METH_KEYWORDS, "Invites a friend to a conference"},
    {"conference_join", (PyCFunction) Tox_conference_join,
     METH_VARARGS | METH_KEYWORDS,
     "Joins a conference that the client has been invited to"},
    {"conference_get_title", (PyCFunction) Tox_conference_get_title,
     METH_VARARGS | METH_KEYWORDS,
     "Return the title designated by the given conference number"},
    {"conference_set_title", (PyCFunction) Tox_conference_set_title,
     METH_VARARGS | METH_KEYWORDS, "Set the conference title and broadcast"
     " it to the rest of the conference"},
    {"conference_get_chatlist", (PyCFunction) Tox_conference_get_chatlist,
     METH_NOARGS, "Return the list of valid conference IDs"},
    {"conference_get_type", (PyCFunction) Tox_conference_get_type,
     METH_VARARGS | METH_KEYWORDS,
     "Returns the type of conference that conference_number is"},
    {"conference_get_id", (PyCFunction) Tox_conference_get_id,
     METH_VARARGS | METH_KEYWORDS, "Get the conference unique ID"},
    {"conference_by_id", (PyCFunction) Tox_conference_by_id,
     METH_VARARGS | METH_KEYWORDS,
     "Return the conference number associated with the specified id"},
    {"friend_send_lossy_packet", (PyCFunction) Tox_friend_send_lossy_packet,
     METH_VARARGS | METH_KEYWORDS, "Send a custom lossy packet to a friend"},
    {"friend_send_lossless_packet",
     (PyCFunction) Tox_friend_send_lossless_packet,
     METH_VARARGS | METH_KEYWORDS,
     "Send a custom lossless packet to a friend"},
    {"callback_friend_lossy_packet",
     (PyCFunction) Tox_callback_friend_lossy_packet,
     METH_VARARGS | METH_KEYWORDS, "Set the callback for the "
     "'friend_lossy_packet' event. Pass None to unset"},
    {"callback_friend_lossless_packet",
     (PyCFunction) Tox_callback_friend_lossless_packet,
     METH_VARARGS | METH_KEYWORDS, "Set the callback for the "
     "'friend_lossless_packet' event. Pass None to unset"},
    {"self_get_dht_id", (PyCFunction) Tox_self_get_dht_id,
     METH_NOARGS, "Get the temporary DHT public key of this instance"},
    {"self_get_udp_port", (PyCFunction) Tox_self_get_udp_port,
     METH_NOARGS, "Return the UDP port this Tox instance is bound to"},
    {"self_get_tcp_port", (PyCFunction) Tox_self_get_tcp_port,
     METH_NOARGS, "Return the TCP port this Tox instance is bound to"},
    {NULL}  /* Sentinel */
};

// Tox type
static PyTypeObject ToxType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "tox.Tox",
    .tp_doc = "Tox object",
    .tp_basicsize = sizeof(ToxObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = Tox_new,
    .tp_init = (initproc) Tox_init,
    .tp_dealloc = (destructor) Tox_dealloc,
    .tp_methods = Tox_methods,
};

/////////////////////////// tox module definiition ////////////////////////////

/* Return Tox library major version. */
static PyObject *
Tox_version_major(PyObject *self)
{
    return PyLong_FromLong(tox_version_major());
}

/* Return Tox library minor version. */
static PyObject *
Tox_version_minor(PyObject *self)
{
    return PyLong_FromLong(tox_version_minor());
}

/* Return Tox library patch or revision number. */
static PyObject *
Tox_version_patch(PyObject *self)
{
    return PyLong_FromLong(tox_version_patch());
}

/* Return whether the compiled library version is compatible with the
   passed version numbers. */
static PyObject *
Tox_version_is_compatible(
    PyObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"major", "minor", "patch", NULL};
    uint32_t major;
    uint32_t minor;
    uint32_t patch;

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "III", kwlist, &major, &minor, &patch))
    {
        return NULL;
    }
    return PyBool_FromLong(tox_version_is_compatible(major, minor, patch));
}

/* The size of a Tox Public Key in bytes. */
static PyObject *
Tox_public_key_size(PyObject *self)
{
    return PyLong_FromLong(tox_public_key_size());
}

/* The size of a Tox Secret Key in bytes. */
static PyObject *
Tox_secret_key_size(PyObject *self)
{
    return PyLong_FromLong(tox_secret_key_size());
}

/* The size of a Tox Conference unique id in bytes. */
static PyObject *
Tox_conference_id_size(PyObject *self)
{
    return PyLong_FromLong(tox_conference_id_size());
}

/* The size of the nospam id in bytes when written in a Tox address. */
static PyObject *
Tox_nospam_size(PyObject *self)
{
    return PyLong_FromLong(tox_nospam_size());
}

/* The size of a Tox address in bytes. */
static PyObject *
Tox_address_size(PyObject *self)
{
    return PyLong_FromLong(tox_address_size());
}

/* Maximum length of a nickname in bytes. */
static PyObject *
Tox_max_name_length(PyObject *self)
{
    return PyLong_FromLong(tox_max_name_length());
}

/* Maximum length of a status message in bytes. */
static PyObject *
Tox_max_status_message_length(PyObject *self)
{
    return PyLong_FromLong(tox_max_status_message_length());
}

/* Maximum length of a friend request message in bytes. */
static PyObject *
Tox_max_friend_request_length(PyObject *self)
{
    return PyLong_FromLong(tox_max_friend_request_length());
}

/* Maximum length of a single message after which it should be split. */
static PyObject *
Tox_max_message_length(PyObject *self)
{
    return PyLong_FromLong(tox_max_message_length());
}

/* Maximum size of custom packets. */
static PyObject *
Tox_max_custom_packet_size(PyObject *self)
{
    return PyLong_FromLong(tox_max_custom_packet_size());
}

/* The number of bytes in a hash generated by tox_hash. */
static PyObject *
Tox_hash_length(PyObject *self)
{
    return PyLong_FromLong(tox_hash_length());
}

/* The number of bytes in a file id. */
static PyObject *
Tox_file_id_length(PyObject *self)
{
    return PyLong_FromLong(tox_file_id_length());
}

/* Maximum file name length for file transfers. */
static PyObject *
Tox_max_filename_length(PyObject *self)
{
    return PyLong_FromLong(tox_max_filename_length());
}

/* Maximum length of a hostname, e.g. proxy or bootstrap node names. */
static PyObject *
Tox_max_hostname_length(PyObject *self)
{
    return PyLong_FromLong(tox_max_hostname_length());
}

/* Generates a cryptographic hash of the given data. */
static PyObject *
Tox_hash(PyObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"data", NULL};
    uint8_t *data;
    size_t length;
    uint8_t hash[TOX_HASH_LENGTH];

    // Parse the input parameters
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "y#", kwlist, &data, &length))
        return NULL;

    // Get the hasl
    tox_hash(hash, data, length);
    return PyBytes_FromStringAndSize(hash, TOX_HASH_LENGTH);
}

// Tox module methods
static PyMethodDef tox_module_methods[] = {
    {"version_major", (PyCFunction) Tox_version_major, METH_NOARGS,
     "Return Tox library major version."},
    {"version_minor", (PyCFunction) Tox_version_minor, METH_NOARGS,
     "Return Tox library minor version."},
    {"version_patch", (PyCFunction) Tox_version_patch, METH_NOARGS,
     "Return Tox library patch or revision number."},
    {"version_is_compatible", (PyCFunction) Tox_version_is_compatible,
     METH_VARARGS | METH_KEYWORDS,
     "Return whether the compiled library version is compatible with the "
     "passed version numbers."},
    {"public_key_size", (PyCFunction) Tox_public_key_size, METH_NOARGS,
     "The size of a Tox Public Key in bytes."},
    {"secret_key_size", (PyCFunction) Tox_secret_key_size, METH_NOARGS,
     "The size of a Tox Secret Key in bytes."},
    {"conference_id_size", (PyCFunction) Tox_secret_key_size, METH_NOARGS,
     "The size of a Tox Conference unique id in bytes."},
    {"nospam_size", (PyCFunction) Tox_nospam_size, METH_NOARGS,
     "The size of the nospam id in bytes when written in a Tox address."},
    {"address_size", (PyCFunction) Tox_address_size, METH_NOARGS,
     "The size of a Tox address in bytes."},
    {"max_name_length", (PyCFunction) Tox_max_name_length, METH_NOARGS,
     "Maximum length of a nickname in bytes."},
    {"max_status_message_length", (PyCFunction) Tox_max_status_message_length,
     METH_NOARGS, "Maximum length of a status message in bytes."},
    {"max_friend_request_length", (PyCFunction) Tox_max_friend_request_length,
     METH_NOARGS, "Maximum length of a friend request message in bytes."},
    {"max_message_length", (PyCFunction) Tox_max_message_length, METH_NOARGS,
     "Maximum length of a single message after which it should be split."},
    {"max_custom_packet_size", (PyCFunction) Tox_max_custom_packet_size,
     METH_NOARGS, "Maximum size of custom packets."},
    {"hash_length", (PyCFunction) Tox_hash_length, METH_NOARGS,
     "The number of bytes in a hash generated by tox_hash."},
    {"file_id_length", (PyCFunction) Tox_file_id_length, METH_NOARGS,
     "The number of bytes in a file id."},
    {"max_filename_length", (PyCFunction) Tox_max_filename_length, METH_NOARGS,
     "Maximum file name length for file transfers."},
    {"max_hostname_length", (PyCFunction) Tox_max_hostname_length, METH_NOARGS,
     "Maximum length of a hostname, e.g. proxy or bootstrap node names."},
    {"hash", (PyCFunction) Tox_hash, METH_VARARGS | METH_KEYWORDS,
     "Generates a cryptographic hash of the given data."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

// tox module
static PyModuleDef toxmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "_tox",
    .m_doc = "Implementation of the Tox protocol.",
    .m_size = -1,
    .m_methods = tox_module_methods,
};

/* Tox module initializer. */
PyMODINIT_FUNC
PyInit__tox(void)
{
    PyObject *m;

    // Finalize the creation of the types
    if (PyType_Ready(&OptionsType) < 0 || PyType_Ready(&ToxType) < 0)
        return NULL;

    // Create the tox module
    m = PyModule_Create(&toxmodule);
    if (m == NULL)
        return NULL;

    // Create the tox.error type exception
    ToxError = PyErr_NewException("tox.error", NULL, NULL);

    // Add tox.error to the module
    Py_XINCREF(ToxError);
    if (PyModule_AddObject(m, "error", ToxError) < 0)
        goto err_toxerror;

    // Add OptionsType to the module
    Py_INCREF(&OptionsType);
    if (PyModule_AddObject(m, "Options", (PyObject *) &OptionsType) < 0)
        goto err_options;

    // Add ToxType to the module
    Py_INCREF(&ToxType);
    if (PyModule_AddObject(m, "Tox", (PyObject *) &ToxType) < 0) {
        goto err_tox;
    }

    // Add constants
    for (int i = 0; i < NUM_ENUMERATES; i++) {
        if (PyModule_AddIntConstant(
            m, tox_enumerates_strings[i], tox_enumerates_values[i]))
        {
            goto err_constants;
        }
    }

    return m;

err_constants:
err_tox:
    Py_DECREF(&ToxType);
err_options:
    Py_DECREF(&OptionsType);
err_toxerror:
    Py_XDECREF(ToxError);
    Py_CLEAR(ToxError);
    Py_DECREF(m);
    return NULL;
}

