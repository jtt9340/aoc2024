{
  description = "Advent of Code 2024";

  inputs = { nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable"; };

  outputs = { self, nixpkgs }: {
    packages.x86_64-linux.default =
      let pkgs = import nixpkgs { system = "x86_64-linux"; };
      in with pkgs;
      stdenv.mkDerivation {
        name = "aoc2024";
        src = self;
        nativeBuildInputs = [ cmake catch2 ];
      };

    devShells.x86_64-linux.default =
      let pkgs = nixpkgs.legacyPackages.x86_64-linux;
      in with pkgs;
      mkShell {
        packages = [ cmake clang-tools ];
        nativeBuildInputs = [ catch2 ];
      };
  };
}
