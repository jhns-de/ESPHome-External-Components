# ESPHome External Components

This repository contains my custom [ESPHome](https://esphome.io) [external components](https://esphome.io/components/external_components.html).

Currently, it includes support for:

- **HANTECH Klima 14000 BTU (4.2 kW)** air conditioner

## Usage

To use these [external components](https://esphome.io/components/external_components.html) in your ESPHome configuration, add the following to your YAML file:

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/jhns-de/ESPHome-External-Components
      # ref: dev  # Uncomment to use the development branch
    components: all
    refresh: 10d

climate:
  - platform: hantech
    name: "AC"
    supports_heat: false
```

## Components

### `hantech` (Climate Component)

Custom ESPHome climate platform to control the **HANTECH Klima 14000 BTU (4.2 kW)** AC unit.

#### Features:

- Cooling, fan-only and dry modes
- Full temperature range in cooling mode (16°C to 31°C)

#### Not (yet) supported:

- Fan speed control
- Swing mode
- Timer functionality *(will not be implemented; use ESPHome or Home Assistant automations instead)*
- Night/sleep mode

## Contributing

Pull requests, issues, and improvements are welcome! If you have another HANTECH model you'd like to see supported, feel free to contribute.

## License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.
