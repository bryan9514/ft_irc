*This project has been created as part of the 42 curriculum by brturcio, salabbe and ntome.*

# ft_irc

## Description

This project is an implementation of an IRC (Internet Relay Chat) server written in C++. The goal is to create a fully functional IRC server that can handle multiple clients, manage channels, and support various IRC commands as defined in the IRC protocol specifications.

The server supports essential IRC features including user registration, channel management, private messaging, and operator commands. It is designed to be compliant with standard IRC protocols while providing a robust and efficient server for chat communications.

## Instructions

### Compilation

To compile the project, run the following command in the root directory:

```
make
```

This will generate the `ircserv` executable.

### Execution

To run the server, use:

```
./ircserv <port> <password>
```

- `<port>`: The port number on which the server will listen for connections.
- `<password>`: The server password required for client connections.

Example:

```
./ircserv 6667 mypassword
```

The server will start and listen for incoming connections on the specified port.

## Resources

### IRC Protocol References
- [RFC 1459 - Internet Relay Chat Protocol](https://tools.ietf.org/html/rfc1459): The original IRC protocol specification.
- [RFC 2810 - Internet Relay Chat: Architecture](https://tools.ietf.org/html/rfc2810): Overview of IRC architecture.
- [RFC 2811 - Internet Relay Chat: Channel Management](https://tools.ietf.org/html/rfc2811): Channel management specifications.
- [RFC 2812 - Internet Relay Chat: Client Protocol](https://tools.ietf.org/html/rfc2812): Client-server protocol details.
- [RFC 2813 - Internet Relay Chat: Server Protocol](https://tools.ietf.org/html/rfc2813): Server-to-server protocol.

### Tutorials and Documentation
- [IRC Protocol Documentation](https://ircdocs.horse/): Comprehensive guide to IRC protocols and implementations.
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/): Useful for understanding socket programming in C/C++.
