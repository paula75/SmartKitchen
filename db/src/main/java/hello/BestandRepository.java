package hello;

import org.springframework.data.jpa.repository.JpaRepository;

// This will be AUTO IMPLEMENTED by Spring into a Bean called userRepository
// CRUD refers Create, Read, Update, Delete

public interface BestandRepository extends JpaRepository<Bestand, Long> {
Bestand findFirst1ByOrderByIdDesc();
}
