{
  description = "Flake for CoasterBuilder";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/24.11";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachSystem [
      "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin"
    ] (system:
      let
        pkgs = import nixpkgs { inherit system; };
        llvm = pkgs.llvmPackages_latest;
      in
        {
          devShells.default = pkgs.mkShell {
            name = "CoasterBuilder-DevShell";
            packages = with pkgs; [
              gcc
              clang
              cmake
              ninja
              bear

              clang-tools

              gdb
              valgrind

              mesa
              libglvnd

              xorg.libX11
              xorg.libXft
              xorg.libXinerama
              xorg.libXrandr
              xorg.libXcursor
              xorg.libXi
            ];

            shellHook = ''
              #export LD_LIBRARY_PATH=${pkgs.xorg.libX11}/lib:${pkgs.libglvnd}/lib:${pkgs.mesa.drivers}/lib:$LD_LIBRARY_PATH
              export LD_LIBRARY_PATH=${pkgs.xorg.libX11}/lib:${pkgs.libglvnd}/lib:${pkgs.mesa.drivers}/lib:$LD_LIBRARY_PATH
            '';
          };

        }
    );
}
