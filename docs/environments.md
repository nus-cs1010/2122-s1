# The CS1010 Programming Environment

C is a common programming language and you can find different implementations of C compiler on many platforms.  Wikipedia [lists more than 40 different C compilers](https://en.wikipedia.org/wiki/List_of_compilers#C_compilers).  These different compilers support different processor architecture, operating systems, may behave slightly differently, and may support different features of C standards.  It is therefore important for CS1010 to stick to a single platform and single compiler.

Our platform of choice is **Ubuntu 18.04 (or later)** using the `clang` compiler (**version 6.0 or later**).

The school has provided a list of computing servers for you to use.  You can access them remotely via `ssh`, or secure shell.  The hosts are named `pe111`, `pe112`, ... , `pe120`.  (`pe` stands for "programming environment").  We will refer to these servers generally as the _PE hosts._

!!! note "pe115 and pe116"
    For this semester, the two servers `pe115` and `pe116` are not available.

You can choose which of the 8 hosts to use.  You share the same home directory across all the hosts (this home directory, however, is different from that of `stu`).

For simplicity, the following guide uses `pe111` in all examples.  Do keep in mind that you can use other hosts for CS1010 to spread out the load.

While it is possible for you to complete the programming assignments on your own computers, the practical exams are done in a controlled environment using servers similar to the PE hosts.  It is therefore advisable for you to familiarize yourself with accessing the PE servers via `ssh` and edit your program with either `vim`.

## Basic Requirements

1. You need to have an SoC UNIX account.  If you do not have one, you can [apply for one online](https://mysoc.nus.edu.sg/~newacct/).

2. Once you have an account, you need to [activate your access to the PE hosts](https://mysoc.nus.edu.sg/~myacct/services.cgi), which is part of the SoC computer clusters.

3. You need an `ssh` client.  macOS and Linux users should already have it installed by default.  Windows 10 users should install [the Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10) and use Linux.

For older versions of Windows, such as those used in the SoC's programming labs, you can check out [XShell 6](https://www.netsarang.com/products/xsh_overview.html) (free for home/school use), or [PuTTY](https://www.putty.org).  These are GUI-based programs so the command lines instructions below do not apply.

## The Command to SSH

Run:
```
ssh <username>@pe111.comp.nus.edu.sg
```

Replace `<username>` with your SoC UNIX username, for instance, I would do:
```
ssh ooiwt@pe111.comp.nus.edu.sg
```

After the command above, following the instructions on the screen.  The first time you ever connect to `pe111.comp.nus.edu.sg`, you will be warned that you are connecting to a previously unknown host.  Say `yes`, and you will be prompted with your SoC UNIX password.

## Accessing The PE Hosts from Outside SoC

The PE hosts can only be accessed from within the School of Computing networks.  If you want to access it from outside, you need to connect through SoC VPN.

First, you need to set up a Virtual Private Network (VPN) (See [instruction here](https://dochub.comp.nus.edu.sg/cf/guides/network/vpn)).  The staff at `helpdesk@comp.nus.edu.sg` or the IT helpdesk in COM1, Level 1, will be able to help with you setting up if needed.

!!! note "SoC VPN vs NUS VPN"

    Note that SoC VPN is different from NUS VPN.  Connecting to NUS VPN only allows you access to the NUS internal network, but not the SoC internal network.

!!! warning "Windows 10 Users: FortiClient from Windows Store"

    Students have reported that running FortiClient downloaded from the Windows Store does not allow one to `ssh` from WSL to SoC hosts as expected.  Therefore, for Windows 10 users, please download and install FortiClient VPN directly from [FortiClient's website](https://forticlient.com/downloads).

## Setting up SSH Keys

Once you are comfortable with UNIX, you can set up a pair of public/private keys for authentication.  

You can use
```
ssh-keygen -t rsa
```

to generate a pair of keys on your local computer.  Keep the private key `id_rsa` on your local machine in the hidden `~/.ssh` directory, and copy the public key `id_rsa.pub` to your home directory on PE `pe111`.  On `pe111`, run
```
cat id_rsa.pub >> ~/.ssh/authorized_keys
```

Make sure that the permission for `.ssh` both on the local machine and on PE are set to `700` and the files `id_rsa` on the local machine and `authorized_keys` on the remote machine are set to `600`.  Once set up, you need not enter your password every time you run `ssh` or `scp`.  

## Stability of Network Connection
    
Note that a stable network connection is required to use the PE hosts for a long period of time without interruption.   If you encounter frequent disconnections while working at home or on campus while connected wirelessly, please make sure that your WiFi signal is strong and there is no interference from other sources. 

## Troubleshooting

Suppose you try to connect to `pe111` using:
```
ssh pe111.comp.nus.edu.sg
```
and you get the following error:

1. `ssh: Could not resolve hostname pe111.comp.nus.edu.sg`

	`ssh` cannot recognize the name `pe111`, it is likely that you are not connected to the SoC VPN, {++or downloaded the wrong version of FortiClient VPN++}.

2. `Connection closed by 192.168.48.xxx port 22`

    You have connected to the PE host, but you are kicked out because you have no permission to use the host.

	Make sure you have activated your access to "SoC computer clusters" here: https://mysoc.nus.edu.sg/~myacct/services.cgi

3. `Permission denied, please try again`

    You did not enter the correct password or username.  Please use the username and password 
of your SoC UNIX account which you have created here: https://mysoc.nus.edu.sg/~newacct/.

    Check that you have entered your username correctly.  It is _case sensitive_.

    If you have lost your password, go here: https://mysoc.nus.edu.sg/~myacct/resetpass.cgi

4. `Could not chdir to home directory /home/o/ooiwt: Permission denied`

    This error means that you have successfully connect to the PE hosts, but you have no access to your own home directory. 

	This should not happen.  Please send an email with the above error message to helpdesk@comp.nus.edu.sg, include the PE hosts that you
	connected to with this error and your username.  The system administrator can reset the permission of your home directory for you.
