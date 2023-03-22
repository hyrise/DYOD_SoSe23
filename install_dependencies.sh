#!/bin/bash

if [[ -z $OPOSSUM_HEADLESS_SETUP ]]; then
    read -p 'This script installs the dependencies of Opossum. It might upgrade already installed packages. Continue? [y|n] ' -n 1 -r < /dev/tty
else
    REPLY="y"
fi

echo
if echo $REPLY | grep -E '^[Yy]$' > /dev/null; then
    unamestr=$(uname)
    if [[ "$unamestr" == 'Darwin' ]]; then
        # Needed for proper building under macOS
        xcode-select --install

        brew --version 2>/dev/null || /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

        echo "Installing dependencies (this may take a while)..."
        if brew update >/dev/null; then
            # check, for each programme individually with brew, whether it is already installed
            # due to brew issues on MacOS after system upgrade
            for formula in boost cmake pkg-config parallel gcovr; do
                # if brew formula is installed
                if brew ls --versions $formula > /dev/null; then
                    continue
                fi
                if ! brew install $formula; then
                    echo "Error during brew formula $formula installation."
                    exit 1
                fi
            done

            if ! brew install llvm; then
                echo "Error during llvm/clang installation."
                exit 1
            fi

            if ! git submodule update --jobs 5 --init --recursive; then
                echo "Error during installation."
                exit 1
            fi
        else
            echo "Error during installation."
            exit 1
        fi
    elif [[ "$unamestr" == 'Linux' ]]; then
        if [ -f /etc/lsb-release ] && cat /etc/lsb-release | grep DISTRIB_ID | grep Ubuntu >/dev/null; then
            echo "Installing dependencies (this may take a while)..."
            if sudo apt-get update >/dev/null; then
                boostall=$(apt-cache search --names-only '^libboost1.[0-9]+-all-dev$' | sort | tail -n 1 | cut -f1 -d' ')
                sudo apt-get install --no-install-recommends -y build-essential gcc-11 clang-15 clang-format-15 clang-tidy-15 llvm-15 cmake parallel python3-pip gcovr $boostall &

                if ! git submodule update --jobs 5 --init --recursive; then
                    echo "Error during installation."
                    exit 1
                fi

                wait $!
                apt=$?
                if [ $apt -ne 0 ]; then
                    echo "Error during installation."
                    exit 1
                fi

                sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 110 --slave /usr/bin/g++ g++ /usr/bin/g++-11
                # The Github Action does not like clang slaves.
                sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 110
                sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-15 110
                sudo update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-15 110
                sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-15 110
                sudo update-alternatives --install /usr/bin/llvm-cov llvm-cov /usr/bin/llvm-cov-15 110

            else
                echo "Error during installation."
                exit 1
            fi
        else
            echo "Unsupported system. You might get the install script to work if you remove the '/etc/lsb-release' line, but you will be on your own."
            exit 1
        fi
    else
        echo "Unsupported operating system $unamestr."
        exit 1
    fi
fi

exit 0
