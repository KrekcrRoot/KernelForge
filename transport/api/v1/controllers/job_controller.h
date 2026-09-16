//
// Created by /<R3/<(RR00T on 12.09.2026.
//

#ifndef KERNELFORGE_JOB_CONTROLLER_H
#define KERNELFORGE_JOB_CONTROLLER_H

#include <drogon/HttpController.h>

// Пример работы с контроллером

namespace KernelForge::api::v1
{

    class JobController final
        : public drogon::HttpController<JobController>
    {

    public:

        METHOD_LIST_BEGIN

        ADD_METHOD_TO(
            JobController::GetJobList,
            "/api/v1/jobs/all",
            drogon::Get
        );

        METHOD_LIST_END

        static void GetJobList(
            const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback
        );

    };

}

#endif //KERNELFORGE_JOB_CONTROLLER_H