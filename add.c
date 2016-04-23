/*
 * SimpleDBus - Simple DBus bindings for Lua
 * Copyright (C) 2008 Emil Renner Berthing <esmil@mailme.dk>
 *
 * SimpleDBus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SimpleDBus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with SimpleDBus. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ALLINONE
#define LUA_LIB
#include <lua.h>
#include <dbus/dbus.h>

#define EXPORT
#endif

enum add_return {
	ADD_OK = 0,
	ADD_ERROR
};

typedef enum add_return (*add_function)(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args);

static add_function get_addfunc(DBusSignatureIter *type);

static enum add_return add_error(lua_State *L, int index, int expected)
{
	lua_pushfstring(L, "(%s expected, got %s)",
			lua_typename(L, expected),
			lua_typename(L, lua_type(L, index)));

	return ADD_ERROR;
}

static enum add_return add_not_implemented(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	lua_pushfstring(L, "(adding type '%s' not implemented yet)",
			dbus_signature_iter_get_signature(type));

	return ADD_ERROR;
}

static enum add_return add_byte(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	unsigned char n;
	if (!lua_isnumber(L, index))
		return add_error(L, index, LUA_TNUMBER);
	n = (unsigned char)lua_tonumber(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_BYTE, &n);
	return ADD_OK;
}

static enum add_return add_boolean(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	dbus_bool_t b;
	if (!lua_isboolean(L, index))
		return add_error(L, index, LUA_TBOOLEAN);
	b = lua_toboolean(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_BOOLEAN, &b);
	return ADD_OK;
}

static enum add_return add_int16(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	dbus_int16_t n;
	if (!lua_isnumber(L, index))
		return add_error(L, index, LUA_TNUMBER);
	n = (dbus_int16_t)lua_tonumber(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_INT16, &n);
	return ADD_OK;
}

static enum add_return add_uint16(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	dbus_uint16_t n;
	if (!lua_isnumber(L, index))
		return add_error(L, index, LUA_TNUMBER);
	n = (dbus_uint16_t)lua_tonumber(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_UINT16, &n);
	return ADD_OK;
}

static enum add_return add_int32(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	dbus_int32_t n;
	if (!lua_isnumber(L, index))
		return add_error(L, index, LUA_TNUMBER);
	n = (dbus_int32_t)lua_tonumber(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_INT32, &n);
	return ADD_OK;
}

static enum add_return add_uint32(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	dbus_uint32_t n;
	if (!lua_isnumber(L, index))
		return add_error(L, index, LUA_TNUMBER);
	n = (dbus_uint32_t)lua_tonumber(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_UINT32, &n);
	return ADD_OK;
}

static enum add_return add_int64(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	dbus_int64_t n;
	if (!lua_isnumber(L, index))
		return add_error(L, index, LUA_TNUMBER);
	n = (dbus_int64_t)lua_tonumber(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_INT64, &n);
	return ADD_OK;
}

static enum add_return add_uint64(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	dbus_uint64_t n;
	if (!lua_isnumber(L, index))
		return add_error(L, index, LUA_TNUMBER);
	n = (dbus_uint64_t)lua_tonumber(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_UINT64, &n);
	return ADD_OK;
}

static enum add_return add_double(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	double d;
	if (!lua_isnumber(L, index))
		return add_error(L, index, LUA_TNUMBER);
	d = (double)lua_tonumber(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_DOUBLE, &d);
	return ADD_OK;
}

static enum add_return add_string(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	const char *s;
	if (!lua_isstring(L, index))
		return add_error(L, index, LUA_TSTRING);
	s = lua_tostring(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_STRING, &s);
	return ADD_OK;
}

static enum add_return add_object_path(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	const char *s;
	if (!lua_isstring(L, index))
		return add_error(L, index, LUA_TSTRING);
	s = lua_tostring(L, index);
	dbus_message_iter_append_basic(args, DBUS_TYPE_OBJECT_PATH, &s);
	return ADD_OK;
}

static enum add_return add_signature(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	const char *s;
	if (!lua_isstring(L, index))
		return add_error(L, index, LUA_TSTRING);
	s = lua_tostring(L, index);
	if (!dbus_signature_validate(s, NULL)) {
		lua_pushfstring(L, "(%s is is not a valid signature)", s);
		return ADD_ERROR;
	}
	dbus_message_iter_append_basic(args, DBUS_TYPE_SIGNATURE, &s);
	return ADD_OK;
}

static enum add_return add_dict_entry(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	DBusSignatureIter array_type;
	DBusSignatureIter dict_type;
	DBusMessageIter array_args;
	DBusMessageIter dict_args;
	char *signature;
	add_function kf;
	add_function vf;

	if (!lua_istable(L, index))
		return add_error(L, index, LUA_TTABLE);

	dbus_signature_iter_recurse(type, &array_type);

	signature = dbus_signature_iter_get_signature(&array_type);

	dbus_signature_iter_recurse(&array_type, &dict_type);

	if (!dbus_type_is_basic(
		dbus_signature_iter_get_current_type(&dict_type))) {
		lua_pushstring(L, "(DICT_ENTRY key must be a basic type)");
	}
	kf = get_addfunc(&dict_type);
	if (!dbus_signature_iter_next(&dict_type)) {
		lua_pushfstring(L, "(DICT_ENTRY must be key-value pair)");
		return ADD_ERROR;
	}
	vf = get_addfunc(&dict_type);
	if (dbus_signature_iter_next(&dict_type)) {
		lua_pushstring(L, "(DICT_ENTRY must be key-value pair)");
		return ADD_ERROR;
	}

	dbus_message_iter_open_container(args, DBUS_TYPE_ARRAY,
			signature, &array_args);

	lua_pushnil(L);
	while (lua_next(L, index)) {
		dbus_message_iter_open_container(&array_args, DBUS_TYPE_DICT_ENTRY,
				NULL, &dict_args);

		dbus_signature_iter_recurse(&array_type, &dict_type);
		int top = lua_gettop(L);
		if (kf(L, top - 1, &dict_type, &dict_args) != ADD_OK) {
			lua_insert(L, -2);
			lua_pop(L, 1);
			return ADD_ERROR;
		}
		dbus_signature_iter_next(&dict_type);
		if (vf(L, top, &dict_type, &dict_args) != ADD_OK) {
			lua_insert(L, -2);
			lua_pop(L, 1);
			return ADD_ERROR;
		}

		lua_pop(L, 1);

		dbus_message_iter_close_container(&array_args, &dict_args);
	}

	lua_pop(L, 1);

	dbus_free(signature);

	dbus_message_iter_close_container(args, &array_args);

	return ADD_OK;
}

static enum add_return add_array(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	DBusSignatureIter array_type;
	DBusMessageIter array_args;
	char *signature;
	add_function af;
	int i;

	if (dbus_signature_iter_get_element_type(type) ==
					DBUS_TYPE_DICT_ENTRY) {
		return add_dict_entry(L, index, type, args);
	}

	if (!lua_istable(L, index))
		return add_error(L, index, LUA_TTABLE);

	dbus_signature_iter_recurse(type, &array_type);

	signature = dbus_signature_iter_get_signature(&array_type);

	dbus_message_iter_open_container(args, DBUS_TYPE_ARRAY,
			signature, &array_args);

	af = get_addfunc(&array_type);

	i = 1;
	while (1) {
		lua_rawgeti(L, index, i);
		if (lua_isnil(L, -1)) {
			lua_pop(L, 1);
			break;
		}

		if (af(L, lua_gettop(L), &array_type, &array_args) != ADD_OK) {
			dbus_free(signature);
			lua_insert(L, -2);
			lua_pop(L, 1);
			return ADD_ERROR;
		}

		lua_pop(L, 1);

		i++;
	}

	dbus_free(signature);

	dbus_message_iter_close_container(args, &array_args);

	return ADD_OK;
}

static enum add_return add_struct(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	DBusSignatureIter struct_type;
	DBusMessageIter struct_args;
	char *signature;
	add_function af;
	int i;

	if (!lua_istable(L, index))
		return add_error(L, index, LUA_TTABLE);

	dbus_signature_iter_recurse(type, &struct_type);

	signature = dbus_signature_iter_get_signature(&struct_type);

	dbus_message_iter_open_container(args, DBUS_TYPE_STRUCT,
			NULL, &struct_args);

	i = 1;
	do {
		lua_rawgeti(L, index, i);

		af = get_addfunc(&struct_type);
		if (af(L, lua_gettop(L), &struct_type, &struct_args) != ADD_OK) {
			dbus_free(signature);
			lua_insert(L, -2);
			lua_pop(L, 1);
			return ADD_ERROR;
		}

		lua_pop(L, 1);

		i++;
	} while (dbus_signature_iter_next(&struct_type));

	dbus_free(signature);

	dbus_message_iter_close_container(args, &struct_args);

	return ADD_OK;
}

static enum add_return add_variant(lua_State *L, int index,
		DBusSignatureIter *type, DBusMessageIter *args)
{
	DBusSignatureIter var_type;
	DBusMessageIter var_args;
	const char *signature = NULL;

	if (!lua_istable(L, index))
		return add_error(L, index, LUA_TTABLE);

	lua_getfield(L, index, "signature");
	signature = lua_tostring(L, -1);
	if (!signature || !dbus_signature_validate_single(signature, NULL)) {
		lua_pop(L, 1);
		lua_pushstring(L, "(invalid variant signature)");
		return ADD_ERROR;
	}

	lua_getfield(L, index, "value");

	dbus_message_iter_open_container(args, DBUS_TYPE_VARIANT,
			signature, &var_args);
	dbus_signature_iter_init(&var_type, signature);

	do {
		add_function af = get_addfunc(&var_type);
		int var_index = lua_gettop(L);
		if (af(L, var_index, &var_type, &var_args) != ADD_OK) {
			lua_insert(L, -3);
			lua_pop(L, 2);
			return 1;
		}
	} while (0);

	dbus_message_iter_close_container(args, &var_args);

	lua_pop(L, 2);

	return ADD_OK;
}

static add_function get_addfunc(DBusSignatureIter *type)
{
	switch (dbus_signature_iter_get_current_type(type)) {
	case DBUS_TYPE_BOOLEAN:
		return add_boolean;
	case DBUS_TYPE_BYTE:
		return add_byte;
	case DBUS_TYPE_INT16:
		return add_int16;
	case DBUS_TYPE_UINT16:
		return add_uint16;
	case DBUS_TYPE_INT32:
		return add_int32;
	case DBUS_TYPE_UINT32:
		return add_uint32;
	case DBUS_TYPE_INT64:
		return add_int64;
	case DBUS_TYPE_UINT64:
		return add_uint64;
	case DBUS_TYPE_DOUBLE:
		return add_double;
	case DBUS_TYPE_STRING:
		return add_string;
	case DBUS_TYPE_OBJECT_PATH:
		return add_object_path;
	case DBUS_TYPE_SIGNATURE:
		return add_signature;
	case DBUS_TYPE_ARRAY:
		return add_array;
	case DBUS_TYPE_STRUCT:
		return add_struct;
	case DBUS_TYPE_VARIANT:
		return add_variant;
	}

	return add_not_implemented;
}

EXPORT unsigned int add_arguments(lua_State *L, int start, int argc,
		const char *signature, DBusMessage *msg)
{
	DBusMessageIter args;
	DBusSignatureIter type;
	int i = start;

	dbus_message_iter_init_append(msg, &args);
	dbus_signature_iter_init(&type, signature);

	if (!dbus_signature_validate(signature, NULL)) {
		lua_pushfstring(L, "type error adding value #%d "
					"of '%s' (invalid signature)",
					i - start + 1, signature);
		return 1;
	}

	do {
		if (i > argc) {
			lua_pushfstring(L, "type error adding value #%d "
					"of '%s' (too few arguments)",
					i - start + 1, signature);
			return 1;
		}

		if ((get_addfunc(&type))(L, i, &type, &args) != ADD_OK) {
			lua_pushfstring(L, "type error adding value #%d of '%s' ",
					i - start + 1, signature);
			lua_insert(L, -2);
			lua_concat(L, 2);
			return 1;
		}

		i++;
	} while (dbus_signature_iter_next(&type));

	return 0;
}
