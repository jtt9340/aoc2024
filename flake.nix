{
  description = "Advent of Code 2024";

  inputs = { nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable"; };

  outputs = { self, nixpkgs }: {
    devShells.x86_64-linux.default =
      let pkgs = nixpkgs.legacyPackages.x86_64-linux;
      in with pkgs;
      mkShell {
        packages = [ cmake clang-tools ];
        nativeBuildInputs = [ catch2 ];
      };
  };
}
