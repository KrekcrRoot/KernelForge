//
// Created by /<R3/<(RR00T on 12.09.2026.
//

#include "job_controller.h"

// Пример работы с контроллером

using namespace KernelForge::api::v1;

void JobController::GetJobList(
    const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback
) {

    const auto res = drogon::HttpResponse::newHttpResponse();
    res->setBody("Hello, Kernel Forge!");

    callback(res);

}
