if (__name__ == "__main__"):
    import os, sys
    from platform import system

    PLATFORM = system().lower()
    KASMOFILE = "kasm.o"
    KASMFILE = "kernel.asm"
    KCOFILE = "kc.o"
    KCFILE = "kernel.c"
    KERNELBIN = "kernel.bin"
    OSNAME = "Griffin OS"
    OUTPUT_PATH = OSNAME+"/boot/"+KERNELBIN
    CWD = os.getcwd()
    QEMU_PKG = "qemu-system-i386"
    GRUBCFG = '''set default=0
set timeout=0

menuentry "'''+OSNAME+'''" {
        set root='(hd96)'
        multiboot /boot/kernel.bin
}
'''
    dependencies = ["nasm", "gcc", "g++", "grub", "xorriso"]
    valid_args = ["crpi", "auto", "help"]

    def checkArgs():
        args = sys.argv.copy()
        length = len(args)
        if (length == 1):
            return "crpi"
        else:
            if (length > 2):
                return "too many args"
            else:
                if (args[1].startswith("-")):
                    return args[1][1::].lower()
                elif (args[1].startswith("/")):
                    return args[1][1::].lower()
                else:
                    return args[1].lower()
                    
            

    def checkNotInstalled():
        required = []
        for pkg in dependencies:
            try: status = os.popen("dpkg -l "+pkg+" 2>/dev/null").read().strip()
            except KeyboardInterrupt: print ("\nAborted (interrupted by user).\n"); sys.exit(1)

            if (status == ''):
                required.append(pkg)
        return required


    def isConnected():
        import socket
        try:
            con = socket.create_connection(("1.1.1.1", 53))
            if (con != None):
                con.close()
            return True
        except OSError:
            pass
        return False


    def installNotInstalled(not_installed):
        failed_install = []
        cmd = ""
        for pkg in not_installed:
            cmd += "sudo apt-get install "+pkg+" 2>buildlog/"+pkg+"_apterror.log"+" 1>buildlog/"+pkg+"_aptout.log;"

        try: os.popen(cmd).read()
        except KeyboardInterrupt: print ("Aborted (interrupted by user).\n"); sys.exit(1)

        for pkg in not_installed:
            errorfile = open("buildlog/"+pkg+"_apterror.log")
            error = errorfile.read()
            errorfile.close()
            if (errorfile != ""):
                failed_install.append(pkg)

        if (len(failed_install) == 0):
            print ("\nAll required package(s) installed successfully.")
        else:
            print ("\nThe following package(s) couldn't be installed:")
            for pkg in failed_install:
                print (pkg, "\t(Log file: "+"buildlog/"+pkg+"_apterror.log)")
            print ("\nPlease see the required log files, resolve the errors and re-run the build script.")
            print ("Aborted (package install error).\n")
            sys.exit(1)


    def runIfNotInstalled(not_installed):
        print ("\nFollowing package(s) need to be installed:")
        for package in not_installed:
            print (package)
        choice = ""
        print ("\nY : Continue\tN : Abort\tR : Use recommended choice")
        print ("Do you want to install the above package(s) now? ", end="")
        while (choice == ""):
            try:
                choice = input("[Y/N/R]: R\033[1D").upper()
                if (choice == ""):
                    choice = "R"
                if (choice not in ("Y", "N", "R")):
                    print ("Invalid choice ", end="")
                    choice = ""
            except KeyboardInterrupt:
                print ("\nAborted (interrupted by user).")
                sys.exit(1)
        if (choice == "Y" or choice == "R"):
            connected = isConnected()
            connected = True
            if (not connected):
                print ("\nLooks like you are not connected to the Internet, or your connection is too slow.",
                "To install the required packages, you need to have an active Internet connection.",
                "\nIf it is possible for you to restore connectivity, please do so and press Enter.",
                "Alternatively, you may press Ctrl+C to abort building the kernel for now.")
                while (True):
                    try:
                        input()
                        connected = isConnected()
                        if (not connected):
                            print ("Still not able to connect. Try again...", end="")
                        else:
                            print ("\nConnection restored. Attempting to install...")
                            break
                    except KeyboardInterrupt:
                        print ("\nAborted (installation cancelled by user).\n")
                        sys.exit(0)
            installNotInstalled(not_installed)
        else:
            print ("Aborted (installation cancelled by user).\n")
            sys.exit(0)


    def runNasm():       
        print ("\nCompiling "+KASMFILE+"...")
        os.popen("nasm -f elf32 "+KASMFILE+" -o "+KASMOFILE+" 2>buildlog/nasm_err.log 1>buildlog/nasm_out.log").read()
        errorfile = open("buildlog/nasm_err.log")
        error = errorfile.read()
        errorfile.close()
        if (error == ""):
            print ("Compiled "+KASMFILE+" successfully. "+"Output file: "+CWD+"/"+KASMOFILE+"\n")
            return 0
        else:
            if (os.path.isfile(KASMOFILE)):
                print ("\nNASM compiled "+KASMFILE+", but with warnings. See below for details:")
                print (error)
                return 1
            else:
                print ("\nNASM failed to compile "+KASMFILE+" successfully. See below for details:")
                print (error)
                return -1
            
                

    def runGcc():
        print ("Compiling "+KCFILE+"...")
        os.popen("gcc -m32 -c "+KCFILE+" -o "+KCOFILE+" -ffreestanding 2>buildlog/gcc_err.log 1>buildlog/gcc_out.log").read()
        errorfile = open("buildlog/gcc_err.log")
        error = errorfile.read()
        errorfile.close()
        if (error == ""):
            print ("Compiled "+KCFILE+" successfully. "+"Output file: "+CWD+"/"+KCOFILE+"\n")
            return 0
        else:
            if (os.path.isfile(KCOFILE)):
                print ("\nGCC compiled "+KCFILE+", but with warnings. See below for details:")
                print (error)
                return 1
            else:
                print ("\nGCC failed to compile "+KCFILE+" successfully. See below for details:")
                print (error)
                return -1
            
            

    def runLinker():
        try:
            os.popen("mkdir "+OSNAME+" 2>/dev/null").read()
            os.popen("mkdir "+OSNAME+"/boot 2>/dev/null").read()
            os.popen("mkdir "+OSNAME+"/boot/grub 2>/dev/null").read()
        except KeyboardInterrupt:
            print ("\nAborted building kernel (interrupted by user).\n"); sys.exit(1)

        print ("Linking "+KASMOFILE+" and "+KCOFILE+"...")            
        os.popen("ld -m elf_i386 -T link.ld -o "+OUTPUT_PATH+" "+KASMOFILE+" "+KCOFILE+" 2>buildlog/ld_err.log 1>buildlog/ld_out.log").read()
        errorfile = open("buildlog/ld_err.log")
        error = errorfile.read()
        errorfile.close()
        if (error == ""):
            print ("Linked "+KASMOFILE+" and "+KCOFILE+" successfully. Output file: "+CWD+"/"+OUTPUT_PATH+"\n")
            return 0
        else:
            if (os.path.isfile(OUTPUT_PATH)):
                print ("\nLinker linked "+KASMOFILE+" and "+KCOFILE+" but with warnings. See below for details:")
                print (error)
                return 1
            else:
                print ("\nLinker failed to link "+KASMOFILE+" and "+KCOFILE+" successfully. See below for details:")
                print (error)
                return -1
            


    def runGrub():
        try:
            os.popen("mkdir "+OSNAME+" 2>/dev/null").read()
            os.popen("mkdir "+OSNAME+"/boot 2>/dev/null").read()
            os.popen("mkdir "+OSNAME+"/boot/grub 2>/dev/null").read()
        except KeyboardInterrupt:
            print ("\nAborted building kernel (interrupted by user).\n"); sys.exit(1)

        if (not os.path.isfile(OSNAME+"/boot/grub/grub.cfg")):
            grubconfig = open (OSNAME+"/boot/grub/grub.cfg", "w")
            grubconfig.write(GRUBCFG)
            grubconfig.close()            
        print ("Generating final binary file for "+OSNAME+"...")
        os.popen("grub-mkrescue -o "+OSNAME+".iso "+OSNAME+"/ 1>buildlog/grub_err.log 2>buildlog/grub_out.log").read() # grub generates stdout on signal 2 instead of signal 1
        errorfile = open("buildlog/grub_err.log")
        error = errorfile.read()
        errorfile.close()
        if (error == ""):
            print ("Done!!! Built "+OSNAME+" successfully. Output ISO file generated at: "+CWD+"/"+OSNAME+".iso")
            print ("Use "+OSNAME+" in a virtual machine or try booting it on real hardware.")
            return 0
        else:
            print ("GRUB failed to generate final ISO image "+OSNAME+".iso. See below for details:")
            print (error)
            return -1
        

    def qemu():
        try:
            status = os.popen("dpkg -l "+QEMU_PKG+" 2>/dev/null").read().strip()
        except KeyboardInterrupt:
            print ("\n")
            return
        if (status == ''):
            print ("Do you want to install the "+QEMU_PKG+" package?\nQEMU is an emulator which can help you run the kernel without the need of creating a virtual machine. ", end="")
            print ("\nY : Continue\tN : Abort\tR : Use recommended choice")
            choice = ""
            while (choice == ""):
                try:
                    choice = input("[Y/N/R]: R\033[1D").upper()
                    if (choice == ""):
                        choice = "R"
                    if (choice not in ("Y", "N", "R")):
                        print ("Invalid choice ", end="")
                        choice = ""
                except KeyboardInterrupt:
                    print ("\n")
                    return
            if (choice in ("Y", "R")):
                installNotInstalled([QEMU_PKG])
            else:
                print ("\n")
                return
        print( "\nRunning "+OSNAME+" in QEMU...")
        os.popen ("qemu-system-i386 -kernel "+OUTPUT_PATH).read()
        print ("QEMU ran successfully and was closed.")





    #############################################################     FUNCTION DEFINITIONS END HERE       #################################################################
    #######################################################################################################################################################################            




    args = checkArgs()

    if (args == "crpi"):

        print ("Welcome to the "+OSNAME+" kernel build utility.\n")

        if (PLATFORM == 'linux'):
            try: os.popen("mkdir buildlog 2>/dev/null").read()
            except KeyboardInterrupt: print ("\nAborted building kernel (interrupted by user)."); sys.exit(1)
            print ("Checking whether required packages are installed...")
            not_installed = checkNotInstalled()
            if (len(not_installed) == 0):
                print ("All required packages are installed.")
            else:
                runIfNotInstalled(not_installed)
            
            # If the code manages to reach here, then it means that the required packages are successfully installed.
            if (runNasm() != -1):
                if (runGcc() != -1):
                    if (runLinker() != -1):
                        if (runGrub() != -1):
                            qemu()
                        else:
                            print ("Build failed. GRUB encountered an error.")
                    else:
                        print ("Build failed. Linker encountered an error.")
                else:
                    print ("Build failed. GCC encountered an error.")
            else:
                print ("Build failed. NASM encountered an error.")

            print ("\nLog files generated during the build process are at: "+CWD+"/buildlog/.\n")
                
        else:
            print ("Error: Build cannot proceed. Your platform is not supported for building "+OSNAME+" (Required: Linux, Found: "+PLATFORM.capitalize()+").")
            print ("What you can try: Install any Linux distro in a virtual machine and run build from there.\n")

    elif (args == "auto"):
        print (OSNAME+" kernel build utility. \nRunning build in auto mode.\n")
        if (PLATFORM == 'linux'):
            try:
                os.popen("mkdir buildlog 2>/dev/null").read()
            except KeyboardInterrupt:
                print ("\nAborted building kernel (interrupted by user)."); sys.exit(1)

            if (runNasm() != -1):
                if (runGcc() != -1):
                    if (runLinker() != -1):
                        if (runGrub() != -1):
                            qemu()
                        else:
                            print ("Build failed. GRUB encountered an error.")
                    else:
                        print ("Build failed. Linker encountered an error.")
                else:
                    print ("Build failed. GCC encountered an error.")
            else:
                print ("Build failed. NASM encountered an error.")

            print ("\nLog files generated during the build process are at: "+CWD+"/buildlog/.\n")

        else:
            print ("Error: Build cannot proceed. Your platform is not supported for building "+OSNAME+" (Required: Linux, Found: "+PLATFORM.capitalize()+").")
            print ("What you can try: Install any Linux distro in a virtual machine and run build from there.\n")


    elif (args == "help"):
        print (OSNAME+" kernel build utility.\nFollowing are the accepted command-line arguments.\n")
        print ("-auto   : Run the build without checking for the availability of required packages. Use this flag only after running build with -crpi atleast once.")
        print ("-help   : Show this help menu.")
        print ("-crpi   : Check whether all the required packages for the build process are installed. You will be prompted if one or more packages need to be installed. (Default)")
        print ("\nAbove arguments are NOT case-sensitive, i.e. -auto is same as -Auto or -AUTO. Only ONE argument is accepted at a time.")
        print ("\nWhen running build with -crpi flag, you will have to enter one of the three options: [Y/N/R]. They mean:")
        print ("Y : Yes (Action will continue)\nN : No (Action will not continue)\nR : Recommended (Action will continue according to the recommended settings)")
        print ("\nPressing enter without entering any value will cause the recommended action to be taken.\n")


    elif (args == "too many args"):
        print ("You passed too many arguments. Only one argument needs to provided.")
        print ("Use -help to get the list of available arguments and additional details.\n")


    else:
        print ("Invalid argument passed. ", end="")
        for arg in valid_args:
            if (args.find(arg) != -1 or args[0] == arg[0]):
                print ("Did you mean -"+arg+" ?")
                break
        print ("Use -help to get the list of available arguments and additional details.\n")
    

else:
    raise ImportError("Module \""+__name__+"\" is not importable.")
