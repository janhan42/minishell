## 허용 함수

readline ,rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs

libft사용 가능

___
## 함수 정리

readline

	#include <readline/readline.h>
	char *readline(const char *str);

str을 출력하고 프롬프트를 열어서 표준 입력으로 문자열을 입력받는다.
개행(엔터)를 받으면 지금까지 입력된 문자열을 리턴한다.
문자열을 입력받기 전까지는 다음 코드로 진행되지 않는다.
반환된 문자열은 사용이 끝난후 free를 사용해서 메모리를 해제 해주어야한다.

```c

#include <readline/readline.h>
#include <stdio.h>
#include <strlib.h>

int main()
{
	char *input = readline("명령어 입력: ");
	printf("입력된 명령어: %s\n", input);
	free(input);
	return (0);
}
```

____
rl_clear_history

	#include <readline/history.h>
	void rl_clear_history(void);

현재까지 누적된 명령어 히스토리를 삭제 합니다.
이 함수 호출 후에는 이전에 입력된 명령어들이 히스토리에서 완전이
제거되어 더 이상 접근할 수 없게 됩니다.

```c
#include <readline/history.h>

int main()
{
	char *input = readline("Enter command: ");

	add_history(input);
	input = readline("Enter next command: ");
	add_hostory(input);
	HIST_ENTRY **the_history = history_list();
	if (the_history)
	{
		for (int i = 0; teh_history[i]; i++)
		printf("%d: %s\n", i + history_base, the_history[i]->line);
	}
	rl_clear_history();
	free(input);
	return (0);
}
```

___

rl_on_new_line

	#include <readline/readline.h>
	void rl_on_new_line(void);

readline이 새로운 입력 줄을 시작할 준비가 되었음을
readline라이브러리에 알리는데 사용된다, 이 함수는
사용자가 새 줄에 입력을 시작하기 전에 내부 readline 상태를 올바르게
재설정하고, 화면 상에 적절하게 표시 될 수 있도록 한다
rl_on_new_line은 특히 여러 줄에 걸친 입력을 처리하거나, 동적인
출력과 사용자 입력이 혼합되는 상황에서 사용한다.

```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/hostory.h>

void custom_print_func()
{
	printf("Custom message before user input.\n");
	rl_on_new_line(); // readline에게 새 줄에서 입력을 시작할 준비가 되었음을 알림
}

int main()
{
	custom_print_func(); // 사용자 입력 전에 커스텀 메세지 출력
	// 사용자로부터 입력 받기
	char *input = readline("Enter your command: ");
	add_history(input); // 입력된 명령어를 히스토리에 추가
	free(input);
	return (0);
}

```

___
rl_replace_line

	#include <readline/readline.h>
	void rl_reaplace_line(const char *text, int clear_undo);

현재 사용자가 입력 중인 텍스트 라인을 지정된 텍스트로 교체하는데 사용된다,
이 함수는 스크립트나 프로그램이 사용자 입력을 동적으로 수정하거나 조정할
필요가 있는 경우에 유용하다, 예를 들어 사용자 입력을 기반으로 자동 완성 기능을 구현하거나,
특정 조건을 만족하는 경우 사용자의 입력을 프로그램 측에서 변경해야 할 때 사용할 수 있다.
clear_undo 가 0이 아닌 값이면 히스토리를 클리어 한다.

```c
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

int main()
{
	// readline 프롬프트 표시 및 사용자 입력 받기.
	char *input = readline("Enter your command: ");
	// 사용자 입력을 'New text'로 교체하기.
	rl_replace_line("New text", 1); // Undo 히스토리도 클리어
	// 수정된 라인을 화면에 다시 표시하기
	rl_redisplay();
	// 후속 작업 (예: 메모리 해제)
	free(input);
	return (0);
}
```



___
rl_redisplay

	#include <readline/readline.h>
	void rl_redisplay(void);

사용자 인터페이스의 현재 상태를 화면에 다시 그리는 데 사용된다.

```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *input = readline("Enter your command: ");
	rl_replace_line("MOdifind text", 1);
	rl_redisplay(); // 위에서 replace로 변경한 사항을 바로 화면에 반영
	free(input);
	return (0);
}
```

___
add_history

	#include <readline/history.h>
	void add_history(const char *line);

사용자가 입력한 명령어 또는 텍스트를 히스토리 목록에 추가하는 데 사용된다,
이 기능은 이전에 실행한 명령어들을 쉽게 다시 호출하고 사용할 수 있게 한다

```c
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *input = readline("Enter your command: ");
	if (input && *input)
	add_history(input);
	printf("Your entered: %s\n", input);
	free(input);
	return (0);
}
```

___

access

	#include <unstdi.h>
	int access(const char *pathname, int mode);
	return value
	성공 시 : 0
	실패 시 : -1 을 반환하고 errno에 오류코드를 설정

pathname: 접근 권한을 검사하고자 하는 파일 또는 디렉토리 경로.
mode: 검사하고자 하는 접근 권한의 유형.
F_OK는 파일 존재 여부만 검사,
R_OK는 파일 읽기 권한
W_OK는 파일 쓰기 권한
X_OK는 파일 실행 권한

```c
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	const char *filepath = "/path/to/file.txt";
	// 파일 존재 여부 검사
	if (access(filepath, F_OK) == 0)
		printf("File exists.\n");
	else
		printf("File does not exist.\n");

	// 파일 읽기 권한 검사
	if (access(filepath, R_OK) == 0)
		printf("Read permission is granted.\n");
	else
		printf("Read permission is denied.\n");
	return (0);
}
```

___

wait3, wait4

	#include <sys/type.h>
	#include <sys/wait.h>
	#include <sys/resource.h>
	pid_t wait3(int *status, int options, struct rusage *rusage);

status: 자식 프로세스의 종료 상태를 저장하는 포인터입니다. 이 값을 통해 자식
프로세스가 어떻게 종료되었는지(예: 정상 종료, 시그널에 의한 종료 등) 알 수 있습니다.
options: waitpid 함수와 유사하게,wait3 호출의 동작을 제어하는 옵션입니다.
WNOHANG, WUNTRACED 등의 플래그를 사용할 수 있습니다.
rusage: 자식 프로세스에 의해 소비된 리소스 사용량을 저장하는 struct rusage 구조체의 포인터입니다.

	#include <sys/type.h>
	#include <sys/wait.h>
	#include <sys/resource.h>
	pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);

pid: 특정 자식 프로세스를 대상으로 할 때, 그 프로세스의 PID를 지정합니다.
wait3와는 달리, 특정 PID나 프로세스 그룹을 지정할 수 있는 기능을 제공합니다.
status: wait3와 마찬가지로, 자식 프로세스의 종료 상태를 저장하는 포인터입니다.
options: wait3에서 설명된 것과 같은 옵션을 지정합니다.
rusage: wait3와 동일하게, 자식 프로세스의 리소스 사용 정보를 저장합니다.
___
signal

	#include <signal.h>
	void (*signal(int sig, void (*func)(int)()))(int);

sig: 처리할 시그널의 번호, 예를 들어 'SIGINT'는 인터럽트 시그널 (프로그램 종료 요청), SIGTERM은 종료 요청 시그널 등이 있다.
func: 해당 시그널을 받았을 때 호출될 함수의 포인터, SIG_IGN으로 설정하면 시그널을 무시하고, SIG_DFL로 설정하면 시그널의 기본 동작을 수행한다, 사용자 정의 함수를 사용할 경우, 그 함수는 int타입의 매개변수를 하나 받아야 하며, 반환타입은 void로 설정한다

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signal)
{
	printf("Receoved signal %d\n", signal);
	//  필요한 처리를 구현
}

int main()
{
	// SIGINT 시그널을 받았을 떄 signal_handler 함수를 호출하도록 설정
	signal(SIGINT, signal_handler);

	// 무한 루프를 돌면서 SIGIN 시그널(일반적으로 Ctrl+C)를 기단린다
	while (1)
	{
		sleep(1) // 1초동안 대기
	}
	return (0);
}
```

Caption
- signal 함수의 동작은 시스템에 따라 다를 수 있으므로, 이식성이 중요한 프로그램에서는 sigaction 함수를 사용하는 것을 더 권자한다.
- 일부 시그널 (예: SIGKILL, SIGSTION)은 잡을 수 없으므로, 이러한 시그널에 대한 핸들러를 설정해도 무시된다.
- 스기널 핸들러 내에서는 가능한 한 제한적인 작업만 수행해야 하며, 특히 블록되는 시스템호출, 복잡한 연산, 또는 printf같은 라이브러리 함수의 호출을 피해야한다.
___
sigaction

	#include <signal.h>
	int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

- signum: 설정하거나 가져올 시그널의 번호.
- act: signum 시그널에 대한 새 동작을 지정하는 sigaction 구조체에 대한 포인터, 시그널이 발생했을때 어떤 동작을 취할 것인지 설명한다.
- oldact: 이전에 signum 시그널에 대해 설정된 sigaction 구조체를 받을 포인터, 이전 설정을 유지하지 않으려면 NULL로 설정할 수 있다

sigaction 구조체
```c
struct sigaction
{
	void (*sa_handler)(int) // 시그널 핸들러 함수 포인터
	void (*sa_sigaction)(int, siginfo_t *, void *)// 추가 정보를 제공하는 핸들러 함수 포인터
	sigset_t sa_mask; // 호출된 핸들러 동안 차단될 추가 시그널
	int sa_flags; // 시그널 처리 옵션 플래그
	void (*sa_restorer)(void); // 사용되지 않음; 호환성을 위해 존재
}
```
- sa_handler: 시그널 핸들러 함수를 지정합니다. SIG_DEL, SIG_INT 또는 사용자 정의 함수를 지정할 수 있습니다.
- sa_sigaction: sa_handler 대신 사용할 수 있는 또 다른 핸들러 함수다, 이 함수는 시그널 번호 외에도 signfo_t 구조체를 통해 시그널에 대핸 추가 정보를 받을 수 있습니다, sa_falags에 SA_SIGINFO플래그가 설정된 경우에만 사용됩니다
- sa_mask: 핸들러 함수 실행 중에 차단될 시그널 집합입니다, 핸들러가 슬행되는 동안 이 시그널들은 처리되지 않습니다.
- sa_flags: 시그널 처리를 제어하기 위한 플래그 집합입니다, 예를 들어 'SA_RESTART'는 시그널 처리 후 시스템 호출이 중단되지 않고 재시작되도록 합니다.
```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
	pritnf("Signal %d received.\n", signum);
}

int main()
{
	struct sigaciton sa;
	sa.sa_handler = handler // 핸들러 함수 설정
	sigmptyset(&sa.sa_mask); // 모든 시그널의 차단을 해제
	sa.sa_flags = 0; // 기본 플래그 사용

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}

	while (1)
	{
		printf("Wating for SIGINT (Ctrl+C)...\n");
		sleep(1);
	}
	return (0);
}
```
___
sigemptyset

	#include <signal.h>
	int sigmptyset(sigset_t *set);
	return value
	성공시 0 을 반환
	실패시 -1 을 반환하고, errno를 설정하여 오류를 나타낸다
	 그러니 실제로 sigemptyset 함수가 실패하는 경우는 거의 없다.

- set: 초기화할 시그널 집홥과 포인터.
-
 시스템에서 시그널 집합을 초기화하여 모든 시그널을 차단하지 않도록 설정하는 C 표준 함수, 이 함수는 시그널 집합을 사용하기 전에 해당 집합을 빈상태로 만들기 위해 사용된다, 주로 sigaction 구조체의 sa_mask 를 초기화 하거나, 시그널을 차단하거나 대기하는 다른 시그널 관련 함수들과 함께 사용된다.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signal)
{
	printf("Received signal %d\n", signal);
	// 시그널 처리 코드
}

int main()
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask); // sa_mask를 초기화 하여 모든 시그널의 차단을 해제
	sa.sa_handler = signal_handler;
	sa.sa_flag = 0; // 기본 플래그 사용.

	if (sigcation(SIGINT, &sa, NULL) != 0)
	{
		perrror("sigaction);
		return (1);
	}

	while (1)
	{
		printf("Running... Press Ctrl+C to Stop.\n",);
		sleep(1);
	}
	return (0);
}
```
이 코드는 SIGINT 시그널을 받았을 때 'signal_handler' 함소를 호출하도록 설정한다. sigemptyset 함순느 sa.sa_mask를 초기화 하여 signal_handler 가 실행 되는 동안 어떤 시가널도 차단되지 않도록 한다, 이러한 방식으로 , 시그널 핸들러는 필요한 경우 다른 시그널을 받울 수 있게 됩다,

sigemptyset함수는 시그널 처리를 구성할 때 시그널 집합을 명확하게 초기화하는 데 중요한 역할을 한다, 이는 시그널 처리의 예즉 가능성과 안정성을 높이는데 기여한다.
___
sigaddset

	#include <signal.h>
	intt sigaddset(sigset_t *set, int signo);

	return value
	성공시 0을 반환
	실패시 -1을 반환하고, errno를 설정하여 오류를 나타낸다.
- set: 시그널을 추가할 시그널 집합의 주소.
- signo: 집합에 추가할 시그널의 번호.

```c
sigset_t set;
sigemptyset(&set); // 시그널 집합을 초기화
sigaddset(&set, SIGINT); // SIGINT 시그널을 집합에 추가
```

이 코드는 먼저 'sigemptyset' 함수를 사용하여 시그널 집합 'set'을 초기화 하고, 이어서 'sigaddset' 함수를 사용하여 'SIGINT' 시그널을 이 집합에 추가합니다, 결과적으로 'set' 집합은 'SIGINT' 시그널만을 포함하게된다, 이렇게 구성된 시그널 집합은 'sigprocmask', 'sigaction' 등의 다른 시스템 호출과 함께 사용하여 프로그램에서 특정 시그널의 처리 방식을 정의할 때 활용할 수 있다.
___
kill

	#include <sys/types.h>
	#include <signal.h>
	int kill(pid_t pid, int sig);

	return value
	성공시 0을반환
	실패시 -1을 반환후, errno를 설정
- pid : 시그널을 받을 프로세스의 포르세스 ID 'pid'깂이 음수일 경우, 시그널은 프로세스 그룹에 전송될 수 있습니다,
- sig : 전송할 시그널의 번호입니다, '0'을 지정하면 실제로 시그널을 전송하지 않고 프로세스의 존재만을 확인할 수 있다,

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
	pid_t pid = /* 대상 프로세스의 PID */

	// SIGINT 시그널을 프로세스에 보내기
	if (kill(pid, SIGINT) == -1)
	{
		perror("kill failed");
		exit(EXIT_FAILURE);
	}
	return (0);
}
```
이 예제에서 'kill' 함수는 특정 프로세스에 'SIGINT' 시그널을 보내어, 일반적으로 프로세스를 종료하도록 요청합니다, 'SIGINT'는 키보드로부터 인터럽트가 발생했을 때 생성되는 시그널과 동일합니다.

Caption

- 'kill' 함수를 사용하여 시그널을 전송할 때, 보내는 프로세스는 받는 프로세스에 대한 적절한 권한(보통은 같은 사용자 또는 루트 권한)을 가져야 합니다.
- 특정 시그널들은 프로세스가 이를 잡아내거나 무시할 수 없게 설계되어 있습니다.(예: 'SIGKILL', 'SIGSTOP',).
- 프로세스 그룹에 시그널을 보낼 때는 'pid' 매개변수에 그룹 ID의 음수 값을 사용합니다.
___
getcwd

	#include <unistd.h>
	char *getcwd(char *buf, size_t size);

	return value
	성공 시: 현재 작업 디렉토리의 절대 경로를 담고 있는 'buf'의 주소를 반환.
	실패시 : 'NULL'을 반환하고, 'errno'를 설정
- buf : 현재 작업 디렉토리의 경로를 저장할 버퍼의 주소, 이 버퍼는 사용자가 제공해야 하며, 충분한 크기를 가지고 있어야 합니다.
- size : 'buf'의 크기입니다. 경로가 이 크기를 초과할 경우, 'NULL'이 반환되고 'errno'는 'ERANGE'로 설정됩니다.
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current working directory: %s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
```
Caption

- buf 에 제공되는 메모리 공간이 충분히 큰지 확인해야한다, POSIX표준은 최소 256바이트의 크기를 권장 하지만, 보다 안전하게 처리하기 위해 'PATH_MAX'상수를 사용하는 것이 좋다, PATH_MAX는 해당 시스템에서 가능한 최대 경로 길이를 정의.
- 동적 메모리 할당을 사용하여 'getcwd'를 호출할 수도 있다, 이 경우 함수가 실패 할 때 할당된 메모리를 적절히 해제해야하는 책임이 있다.
___
chdir

	#include <unistd.h>
	int chdir(const char *path);

	return value
	성공 시 : 0을 반환.
	실패 시 : -1을 반환하고, 'errno' 변수를 설정, 실패의 원인으로는 'path'가 존재하지 않거나, 접근 권한이 없는 경우 등이 있을 수 있다.
- path : 현재 작업 디렉토리로 변경하고자 하는 디렉토리 경로를 가르키는 문자열.
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	const char *newDir = "/path/to/new/directory";

	if (chdir(newDir) == 0)
		printf("Changed the current working directory to %s\n", newDir);
	else
	{
		perror("chdir failed");
		return (errno);
	}
	return (EXIT_SUCCESS);
}
```
Caption

- chdir 함수는 프그램의 전역 상태를 변경합니다. 따라서, 멀시스레드 환경에스는 현자 작업 디렉토리를 변경하면 모든 스레드에 영향을 준다.
- 보안상의 이유로, 프로그램이 민감한 작업을 수행하기 전에는 항상 현재 디렉토리의 변경이 성공했는지 확인해야한다. 이는 디렉토리 변경 실패가 보안 취약점으로 이어질 수 있기 때문이다.
- chdir를 사용한 후에는 getcwd 함수 등을 사용하여 현재 디렉토리가 예상한 대로 변경되었는지 확인 하는것이 좋다.
___
stat

	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
	int stat(const char *path, struct stat *buf);

stat 함수는 지정된 경로의 파일에 대한 상태 정보를 얻는다, 심볼릭 링크의 경우, 링링크크가  가리키는 실제 파일의 상태 정보를 반환한다.
- path : 상태 정보를 얻고자 하는 파일의 경로.
- buf : 파일의 상태 정보를 저장할 'struct stat' 구조체의 주소.
---
lstat

	#include <sys/type.h>
	#include <sys/stat.h>
	#include <unistd.h>
	int lstat(const char *path, strcut stat *buf);
