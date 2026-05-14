

- https://docs.python.org/3.10/howto/logging.html
- https://docs.python.org/3.10/howto/logging-cookbook.html


### What is "logging" in Python?

Logging in Python is the process of tracking events that happen when some software runs. The logging module in Python is a standard module designed to provide a flexible framework for emitting log messages from Python programs.

### Why is it necessary?

Logging is essential for:
- **Debugging**: Helps track the flow and state of a program during development and debugging.
- **Monitoring**: Allows monitoring of a running application to ensure it behaves as expected.
- **Auditing**: Provides a history of events and actions taken by the software, useful for auditing and compliance.
- **Error Tracking**: Helps capture and record errors and exceptions, facilitating troubleshooting.


### How does it work?

The `logging` module provides a hierarchical logging system with different severity levels:

1. **DEBUG**: Detailed information, typically of interest only when diagnosing problems.
2. **INFO**: Confirmation that things are working as expected.
3. **WARNING**: An indication that something unexpected happened, or indicative of some problem in the near future (e.g., ‘disk space low’). The software is still working as expected.
4. **ERROR**: Due to a more serious problem, the software has not been able to perform some function.
5. **CRITICAL**: A very serious error, indicating that the program itself may be unable to continue running.

### Methods available in `logging`:

The primary methods of the `logging` module include:

- `logging.basicConfig()`: Configures the logging system.
- `logging.getLogger()`: Returns a logger instance.
- `Logger.setLevel()`: Sets the logging level.
- `Logger.addHandler()`: Adds a handler to the logger.
- `Logger.removeHandler()`: Removes a handler from the logger.
- `Logger.debug()`, `Logger.info()`, `Logger.warning()`, `Logger.error()`, `Logger.critical()`: Logs a message with the corresponding severity level.


### Best practices and strategies for using logging:

1. **Use Different Loggers**: Use different loggers for different parts of your application to have more granular control over logging.
2. **Set Appropriate Logging Levels**: Use the appropriate logging levels for messages to avoid clutter and ensure important messages are logged.
3. **Log to Multiple Destinations**: Use handlers to log messages to different destinations (e.g., console, file, remote server).
4. **Structured Logging**: Log structured data (e.g., JSON) to enable easier parsing and analysis.
5. **Avoid Logging Sensitive Information**: Be cautious not to log sensitive information.

```
какие есть уровни логирования?
какие типы логирования?
куда сгружаются логи и как?
в какой папке создается файл с логированием?
как его указывать? полный путь?

```

### Connected terms:

- **Handler**: Determines where the log messages go.
- **Formatter**: Specifies the layout of log messages.
- **Filter**: Provides a fine-grained control over which log records are emitted.
- **Logger**: An object used to log messages.

### Deep technical features:

1. **Thread Safety**: The logging module is designed to be thread-safe.
2. **Custom Handlers**: You can define your own handlers by extending the `logging.Handler` class.
3. **Configuration via Dictionary**: You can configure logging using a dictionary-based configuration.
4. **Propagating Messages**: Loggers can propagate messages to their ancestor loggers.


### Optimizing code with logging:

- **Lazy Evaluation**: Use lazy evaluation to avoid the overhead of logging when it’s not needed. For example, `logger.debug('Message with %s', expensive_function())` defers the call to `expensive_function()` until the message actually needs to be logged.
- **Effective Filtering**: Use filters to ensure only necessary logs are processed and stored.
- **Configuring Handlers Appropriately**: Use appropriate handlers to avoid performance bottlenecks, e.g., use `RotatingFileHandler` for file logging to avoid excessively large log files.


```
what is lazy evaluation?
is that %s?

```
### Comparison to other approaches:

- **Print Statements**: Logging is more flexible and manageable than using print statements, offering better control over output formatting, levels, and destinations.
- **Third-Party Logging Libraries**: Libraries like `loguru` offer more features and simpler syntax but may not be necessary for all projects.


### Examples:

```python
import logging

# Basic configuration
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')

# Create a logger
logger = logging.getLogger('exampleLogger')

# Log messages with different severity levels
logger.debug('This is a debug message')
logger.info('This is an info message')
logger.warning('This is a warning message')
logger.error('This is an error message')
logger.critical('This is a critical message')

# Creating and configuring a file handler
file_handler = logging.FileHandler('example.log')
file_handler.setLevel(logging.ERROR)
file_handler.setFormatter(logging.Formatter('%(asctime)s - %(levelname)s - %(message)s'))
logger.addHandler(file_handler)

# Logging an error to the file
logger.error('This error message will be logged to the file')

```


