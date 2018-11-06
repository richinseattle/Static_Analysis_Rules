static int parse_uint8(DeviceState *dev, Property *prop, const char *str)
{
    uint8_t *ptr = qdev_get_prop_ptr(dev, prop);
    char *end;

    /
    *ptr = strtoul(str, &end, 0);
    if ((*end != '\0') || (end == str)) {
        return -EINVAL;
    }

    return 0;
}
