# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rlfw_msgs:srv/RLSrv.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RLSrv_Request(type):
    """Metaclass of message 'RLSrv_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rlfw_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rlfw_msgs.srv.RLSrv_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__rl_srv__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__rl_srv__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__rl_srv__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__rl_srv__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__rl_srv__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RLSrv_Request(metaclass=Metaclass_RLSrv_Request):
    """Message class 'RLSrv_Request'."""

    __slots__ = [
        '_request_communication_center_parameter',
    ]

    _fields_and_field_types = {
        'request_communication_center_parameter': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.request_communication_center_parameter = kwargs.get('request_communication_center_parameter', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.request_communication_center_parameter != other.request_communication_center_parameter:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def request_communication_center_parameter(self):
        """Message field 'request_communication_center_parameter'."""
        return self._request_communication_center_parameter

    @request_communication_center_parameter.setter
    def request_communication_center_parameter(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'request_communication_center_parameter' field must be of type 'str'"
        self._request_communication_center_parameter = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RLSrv_Response(type):
    """Metaclass of message 'RLSrv_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rlfw_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rlfw_msgs.srv.RLSrv_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__rl_srv__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__rl_srv__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__rl_srv__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__rl_srv__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__rl_srv__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RLSrv_Response(metaclass=Metaclass_RLSrv_Response):
    """Message class 'RLSrv_Response'."""

    __slots__ = [
        '_com_name',
        '_com_type',
        '_joint_name',
    ]

    _fields_and_field_types = {
        'com_name': 'sequence<string>',
        'com_type': 'sequence<string>',
        'joint_name': 'sequence<string>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.com_name = kwargs.get('com_name', [])
        self.com_type = kwargs.get('com_type', [])
        self.joint_name = kwargs.get('joint_name', [])

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.com_name != other.com_name:
            return False
        if self.com_type != other.com_type:
            return False
        if self.joint_name != other.joint_name:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def com_name(self):
        """Message field 'com_name'."""
        return self._com_name

    @com_name.setter
    def com_name(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'com_name' field must be a set or sequence and each value of type 'str'"
        self._com_name = value

    @builtins.property
    def com_type(self):
        """Message field 'com_type'."""
        return self._com_type

    @com_type.setter
    def com_type(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'com_type' field must be a set or sequence and each value of type 'str'"
        self._com_type = value

    @builtins.property
    def joint_name(self):
        """Message field 'joint_name'."""
        return self._joint_name

    @joint_name.setter
    def joint_name(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'joint_name' field must be a set or sequence and each value of type 'str'"
        self._joint_name = value


class Metaclass_RLSrv(type):
    """Metaclass of service 'RLSrv'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rlfw_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rlfw_msgs.srv.RLSrv')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__rl_srv

            from rlfw_msgs.srv import _rl_srv
            if _rl_srv.Metaclass_RLSrv_Request._TYPE_SUPPORT is None:
                _rl_srv.Metaclass_RLSrv_Request.__import_type_support__()
            if _rl_srv.Metaclass_RLSrv_Response._TYPE_SUPPORT is None:
                _rl_srv.Metaclass_RLSrv_Response.__import_type_support__()


class RLSrv(metaclass=Metaclass_RLSrv):
    from rlfw_msgs.srv._rl_srv import RLSrv_Request as Request
    from rlfw_msgs.srv._rl_srv import RLSrv_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
