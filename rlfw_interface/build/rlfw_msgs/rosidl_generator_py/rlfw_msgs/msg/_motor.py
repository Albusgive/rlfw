# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rlfw_msgs:msg/Motor.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Motor(type):
    """Metaclass of message 'Motor'."""

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
                'rlfw_msgs.msg.Motor')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__motor
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__motor
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__motor
            cls._TYPE_SUPPORT = module.type_support_msg__msg__motor
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__motor

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


class Motor(metaclass=Metaclass_Motor):
    """Message class 'Motor'."""

    __slots__ = [
        '_jointname',
        '_motor_id',
        '_angle',
        '_number_laps',
        '_ang_vel',
        '_torque',
        '_current',
        '_temperature',
        '_state',
    ]

    _fields_and_field_types = {
        'jointname': 'std_msgs/Header',
        'motor_id': 'int8',
        'angle': 'float',
        'number_laps': 'float',
        'ang_vel': 'float',
        'torque': 'float',
        'current': 'float',
        'temperature': 'float',
        'state': 'int8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.jointname = kwargs.get('jointname', Header())
        self.motor_id = kwargs.get('motor_id', int())
        self.angle = kwargs.get('angle', float())
        self.number_laps = kwargs.get('number_laps', float())
        self.ang_vel = kwargs.get('ang_vel', float())
        self.torque = kwargs.get('torque', float())
        self.current = kwargs.get('current', float())
        self.temperature = kwargs.get('temperature', float())
        self.state = kwargs.get('state', int())

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
        if self.jointname != other.jointname:
            return False
        if self.motor_id != other.motor_id:
            return False
        if self.angle != other.angle:
            return False
        if self.number_laps != other.number_laps:
            return False
        if self.ang_vel != other.ang_vel:
            return False
        if self.torque != other.torque:
            return False
        if self.current != other.current:
            return False
        if self.temperature != other.temperature:
            return False
        if self.state != other.state:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def jointname(self):
        """Message field 'jointname'."""
        return self._jointname

    @jointname.setter
    def jointname(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'jointname' field must be a sub message of type 'Header'"
        self._jointname = value

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
    def angle(self):
        """Message field 'angle'."""
        return self._angle

    @angle.setter
    def angle(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'angle' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'angle' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._angle = value

    @builtins.property
    def number_laps(self):
        """Message field 'number_laps'."""
        return self._number_laps

    @number_laps.setter
    def number_laps(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'number_laps' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'number_laps' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._number_laps = value

    @builtins.property
    def ang_vel(self):
        """Message field 'ang_vel'."""
        return self._ang_vel

    @ang_vel.setter
    def ang_vel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ang_vel' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'ang_vel' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._ang_vel = value

    @builtins.property
    def torque(self):
        """Message field 'torque'."""
        return self._torque

    @torque.setter
    def torque(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'torque' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'torque' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._torque = value

    @builtins.property
    def current(self):
        """Message field 'current'."""
        return self._current

    @current.setter
    def current(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'current' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'current' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._current = value

    @builtins.property
    def temperature(self):
        """Message field 'temperature'."""
        return self._temperature

    @temperature.setter
    def temperature(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'temperature' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'temperature' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._temperature = value

    @builtins.property
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'state' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'state' field must be an integer in [-128, 127]"
        self._state = value
