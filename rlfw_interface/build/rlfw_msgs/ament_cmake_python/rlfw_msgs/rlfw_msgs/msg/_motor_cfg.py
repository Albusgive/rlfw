# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rlfw_msgs:msg/MotorCfg.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MotorCfg(type):
    """Metaclass of message 'MotorCfg'."""

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
                'rlfw_msgs.msg.MotorCfg')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__motor_cfg
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__motor_cfg
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__motor_cfg
            cls._TYPE_SUPPORT = module.type_support_msg__msg__motor_cfg
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__motor_cfg

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MotorCfg(metaclass=Metaclass_MotorCfg):
    """Message class 'MotorCfg'."""

    __slots__ = [
        '_joint',
        '_motor_id',
        '_parameter_type',
        '_parameter',
    ]

    _fields_and_field_types = {
        'joint': 'std_msgs/Header',
        'motor_id': 'int8',
        'parameter_type': 'string',
        'parameter': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.joint = kwargs.get('joint', Header())
        self.motor_id = kwargs.get('motor_id', int())
        self.parameter_type = kwargs.get('parameter_type', str())
        self.parameter = kwargs.get('parameter', float())

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
        if self.joint != other.joint:
            return False
        if self.motor_id != other.motor_id:
            return False
        if self.parameter_type != other.parameter_type:
            return False
        if self.parameter != other.parameter:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def joint(self):
        """Message field 'joint'."""
        return self._joint

    @joint.setter
    def joint(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'joint' field must be a sub message of type 'Header'"
        self._joint = value

    @builtins.property
    def motor_id(self):
        """Message field 'motor_id'."""
        return self._motor_id

    @motor_id.setter
    def motor_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'motor_id' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'motor_id' field must be an integer in [-128, 127]"
        self._motor_id = value

    @builtins.property
    def parameter_type(self):
        """Message field 'parameter_type'."""
        return self._parameter_type

    @parameter_type.setter
    def parameter_type(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'parameter_type' field must be of type 'str'"
        self._parameter_type = value

    @builtins.property
    def parameter(self):
        """Message field 'parameter'."""
        return self._parameter

    @parameter.setter
    def parameter(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'parameter' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'parameter' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._parameter = value
