*This project has been created as part of the 42 curriculum by brturcio, salabbe and ntome.*

# ft_irc

- **EN:** A compact IRC (Internet Relay Chat) server written in **C++** (42 curriculum project).
- **ES:** Un servidor IRC (Internet Relay Chat) compacto escrito en **C++** (proyecto del currículo de 42).

---

## EN

A compact IRC server that accepts multiple concurrent clients, manages channels, and implements a subset of the IRC client protocol.

### Table of contents

- [Features](#features)
- [Supported commands](#supported-commands)
- [Build](#build)
- [Run](#run)
- [Connect with an IRC client](#connect-with-an-irc-client)
- [Project layout](#project-layout)
- [Notes](#notes)
- [Resources](#resources)

### Features

- TCP server with multiple clients (single-process, event-driven)
- Password-protected connections
- User registration flow (`PASS`, `NICK`, `USER`)
- Channel management (join/leave, invite-only, topic, operators, etc.)
- Private messaging
- IRC numeric replies (see `includes/IrcCodes.hpp`)
- Bonus: simple bot (see `sources/Commands/Bot_bonus.cpp`)

### Supported commands

Implemented command handlers live in `sources/Commands/`:

- Registration: `PASS`, `NICK`, `USER`
- Session: `QUIT`
- Messaging: `PRIVMSG`
- Channels: `JOIN`, `INVITE`, `KICK`, `TOPIC`, `MODE`

> Note: IRC clients differ in the exact command sequence they send. If you have trouble connecting, make sure you provide the server password and complete registration (PASS/NICK/USER).

### Build

From the repository root:

```bash
make
```

This produces the `ircserv` binary.

Useful targets (if present in the Makefile):

```bash
make re
make fclean
```

### Run

```bash
./ircserv <port> <password>
```

- `<port>`: listening port (e.g. `6667`)
- `<password>`: required by clients via `PASS`

Example:

```bash
./ircserv 6667 mypassword
```

### Connect with an IRC client

#### Using netcat (quick smoke test)

```bash
nc 127.0.0.1 6667
PASS mypassword
NICK alice
USER alice 0 * :Alice
JOIN #42
PRIVMSG #42 :hello from nc
```

#### Using an IRC client (HexChat / irssi / weechat)

- Server/Host: `127.0.0.1`
- Port: the `<port>` you chose
- Server password: the `<password>` you started the server with

Then join a channel, for example: `/join #42`.

### Project layout

```text
.
├── includes/
│   ├── Server.hpp        # core server class
│   ├── Client.hpp        # client state
│   ├── Channel.hpp       # channel state
│   ├── ChannelRules.hpp  # modes / permissions
│   ├── Topic.hpp         # topic handling
│   └── IrcCodes.hpp      # numeric replies / codes
├── sources/
│   ├── main.cpp
│   ├── Server*.cpp       # socket + main loop utilities
│   ├── Parsing.cpp       # parsing helpers
│   ├── SplitString.cpp
│   └── Commands/         # command implementations
├── Makefile
└── en.subject.pdf
```

### Notes

- This repository is meant as an educational implementation; it is not intended to be a production-grade IRCd.
- If you want to extend it, a good next step is to add more command handlers under `sources/Commands/` and map them in the server’s command dispatcher.

### Resources

#### IRC Protocol References

- [RFC 1459 - Internet Relay Chat Protocol](https://tools.ietf.org/html/rfc1459)
- [RFC 2810 - Internet Relay Chat: Architecture](https://tools.ietf.org/html/rfc2810)
- [RFC 2811 - Internet Relay Chat: Channel Management](https://tools.ietf.org/html/rfc2811)
- [RFC 2812 - Internet Relay Chat: Client Protocol](https://tools.ietf.org/html/rfc2812)
- [RFC 2813 - Internet Relay Chat: Server Protocol](https://tools.ietf.org/html/rfc2813)

#### Tutorials and Documentation

- [IRC Protocol Documentation](https://ircdocs.horse/)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)

---

## ES

Servidor IRC compacto que acepta múltiples clientes concurrentes, gestiona canales e implementa un subconjunto del protocolo IRC (cliente-servidor).

### Índice

- [Características](#características)
- [Comandos soportados](#comandos-soportados)
- [Compilación](#compilación)
- [Ejecución](#ejecución)
- [Conectarse con un cliente IRC](#conectarse-con-un-cliente-irc)
- [Estructura del proyecto](#estructura-del-proyecto)
- [Notas](#notas-1)
- [Recursos](#recursos-1)

### Características

- Servidor TCP con múltiples clientes (single-process, orientado a eventos)
- Conexiones protegidas por contraseña
- Flujo de registro de usuario (`PASS`, `NICK`, `USER`)
- Gestión de canales (join/leave, invite-only, topic, operadores, etc.)
- Mensajería privada
- Respuestas numéricas IRC (ver `includes/IrcCodes.hpp`)
- Bonus: bot simple (ver `sources/Commands/Bot_bonus.cpp`)

### Comandos soportados

Los handlers de comandos están en `sources/Commands/`:

- Registro: `PASS`, `NICK`, `USER`
- Sesión: `QUIT`
- Mensajería: `PRIVMSG`
- Canales: `JOIN`, `INVITE`, `KICK`, `TOPIC`, `MODE`

> Nota: los clientes IRC pueden enviar secuencias de comandos diferentes. Si tienes problemas para conectar, asegúrate de enviar `PASS` con la contraseña correcta y completar el registro con `NICK` y `USER`.

### Compilación

Desde la raíz del repositorio:

```bash
make
```

Esto genera el binario `ircserv`.

Otros targets útiles (si están definidos en el `Makefile`):

```bash
make re
make fclean
```

### Ejecución

```bash
./ircserv <puerto> <password>
```

- `<puerto>`: puerto de escucha (por ejemplo `6667`)
- `<password>`: contraseña requerida por los clientes mediante `PASS`

Ejemplo:

```bash
./ircserv 6667 mypassword
```

### Conectarse con un cliente IRC

#### Usando netcat (prueba rápida)

```bash
nc 127.0.0.1 6667
PASS mypassword
NICK alice
USER alice 0 * :Alice
JOIN #42
PRIVMSG #42 :hola desde nc
```

#### Usando un cliente IRC (HexChat / irssi / weechat)

Configura:

- Servidor/Host: `127.0.0.1`
- Puerto: el `<puerto>` elegido
- Password del servidor: el `<password>` con el que arrancaste `ircserv`

Luego únete a un canal, por ejemplo: `/join #42`.

### Estructura del proyecto

```text
.
├── includes/
│   ├── Server.hpp        # clase principal del servidor
│   ├── Client.hpp        # estado del cliente
│   ├── Channel.hpp       # estado del canal
│   ├── ChannelRules.hpp  # modos / permisos del canal
│   ├── Topic.hpp         # gestión del topic
│   └── IrcCodes.hpp      # códigos / replies numéricos
├── sources/
│   ├── main.cpp
│   ├── Server*.cpp       # socket + loop principal y utilidades
│   ├── Parsing.cpp       # helpers de parseo
│   ├── SplitString.cpp
│   └── Commands/         # implementación de comandos
├── Makefile
└── en.subject.pdf
```

### Notas

- Implementación educativa: no está pensada como un IRCd para producción.
- Para ampliarlo, un buen siguiente paso es añadir nuevos handlers en `sources/Commands/` y registrarlos en el dispatcher de comandos del servidor.

### Recursos

#### Referencias del protocolo IRC

- [RFC 1459 - Internet Relay Chat Protocol](https://tools.ietf.org/html/rfc1459)
- [RFC 2810 - Internet Relay Chat: Architecture](https://tools.ietf.org/html/rfc2810)
- [RFC 2811 - Internet Relay Chat: Channel Management](https://tools.ietf.org/html/rfc2811)
- [RFC 2812 - Internet Relay Chat: Client Protocol](https://tools.ietf.org/html/rfc2812)
- [RFC 2813 - Internet Relay Chat: Server Protocol](https://tools.ietf.org/html/rfc2813)

#### Tutoriales y documentación

- [IRC Protocol Documentation](https://ircdocs.horse/)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
